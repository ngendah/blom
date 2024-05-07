/*
 * Copyright 2022 Google LLC.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "decision_forest.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/memory/memory.h"
#include "absl/status/status.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "dataset/data_spec.pb.h"
#include "dataset/vertical_dataset.h"
#include "dataset/vertical_dataset_io.h"
#include "model/abstract_model.h"
#include "model/decision_tree/decision_tree.h"
#include "model/decision_tree/decision_tree.pb.h"
#include "model/fast_engine_factory.h"
#include "model/model_library.h"
#include "serving/decision_forest/decision_forest_serving.h"
#include "serving/decision_forest/register_engines.h"
#include "utils/concurrency.h"  // IWYU pragma: keep
#include "utils/csv.h"
#include "utils/filesystem.h"
#include "utils/logging.h"
#include "utils/status_macros.h"  // IWYU pragma: keep
#include "utils/test.h"
#include "e2e_test_utils/test_utils.h"

namespace yggdrasil_decision_forests {
namespace serving {
namespace decision_forest {
namespace {

using model::random_forest::RandomForestModel;
using testing::ElementsAre;

std::string TestDataDir() {
  return file::JoinPath(test::DataRootDirectory(),
                        "yggdrasil_decision_forests/test_data");
}

// Loads a header-less csv containing a single numerical column.
std::vector<float> LoadCsvToVectorOfFloat(const absl::string_view path) {
  std::vector<float> result;
  file::InputFileCloser closer(std::move(file::OpenInputFile(path).value()));
  yggdrasil_decision_forests::utils::csv::Reader reader(closer.stream());
  std::vector<absl::string_view>* row;
  while (reader.NextRow(&row).value()) {
    CHECK_EQ(row->size(), 1);
    float value;
    CHECK(absl::SimpleAtof((*row)[0], &value));
    result.push_back(value);
  }
  return result;
}

// Load a dataset
dataset::VerticalDataset LoadDataset(
    const dataset::proto::DataSpecification& data_spec,
    const absl::string_view dataset_filename,
    const absl::string_view format = "csv") {
  const std::string ds_typed_path = absl::StrCat(
      format, ":", file::JoinPath(TestDataDir(), "dataset", dataset_filename));
  dataset::VerticalDataset dataset;
  CHECK_OK(LoadVerticalDataset(ds_typed_path, data_spec, &dataset));
  return dataset;
}

// Load a model.
std::unique_ptr<model::AbstractModel> LoadModel(
    const absl::string_view model_dirname) {
  const std::string model_dir =
      file::JoinPath(TestDataDir(), "model", model_dirname);
  std::unique_ptr<model::AbstractModel> model;
  CHECK_OK(model::LoadModel(model_dir, &model));
  return model;
}

// Ensures that the model is compatible with the following set of engines.
void CheckCompatibleEngine(
    const model::AbstractModel& model,
    const std::unordered_set<std::string>& expected_engines) {
  std::unordered_set<std::string> compatible_engines;
  auto engine_factories = model.ListCompatibleFastEngines();
  for (auto& factory : engine_factories) {
    EXPECT_OK(factory->CreateEngine(&model).status());
    compatible_engines.insert(factory->name());
  }

  if (expected_engines != compatible_engines) {
    YDF_LOG(INFO) << "expected_engines:"
                  << absl::StrJoin(expected_engines, " ");
    YDF_LOG(INFO) << "compatible_engines:"
                  << absl::StrJoin(compatible_engines, " ");
    ADD_FAILURE();
  }
}

TEST(SpecializedRandomForestTest,
     BinaryClassificationNumericalOnlyFlatNodeGenericToSpecializedModel) {
  model::random_forest::RandomForestModel rf_model;
  auto tree = absl::make_unique<model::decision_tree::DecisionTree>();
  tree->CreateRoot();
  tree->mutable_root()->CreateChildren();
  tree->mutable_root()->mutable_node()->mutable_condition()->set_attribute(1);
  tree->mutable_root()
      ->mutable_node()
      ->mutable_condition()
      ->mutable_condition()
      ->mutable_higher_condition()
      ->set_threshold(2.f);
  tree->mutable_root()
      ->mutable_pos_child()
      ->mutable_node()
      ->mutable_classifier()
      ->set_top_value(1);
  tree->mutable_root()
      ->mutable_neg_child()
      ->mutable_node()
      ->mutable_classifier()
      ->set_top_value(2);
  rf_model.AddTree(std::move(tree));
  rf_model.set_task(model::proto::Task::CLASSIFICATION);
  rf_model.set_label_col_idx(3);
  rf_model.mutable_input_features()->push_back(1);

  auto* col_0 = rf_model.mutable_data_spec()->add_columns();
  col_0->set_name("col_0");
  col_0->set_type(dataset::proto::ColumnType::NUMERICAL);
  col_0->mutable_numerical()->set_mean(3.f);

  auto* col_1 = rf_model.mutable_data_spec()->add_columns();
  col_1->set_name("col_1");
  col_1->set_type(dataset::proto::ColumnType::NUMERICAL);
  col_1->mutable_numerical()->set_mean(4.f);

  auto* label = rf_model.mutable_data_spec()->add_columns();
  label->set_name("label");
  label->set_type(dataset::proto::ColumnType::CATEGORICAL);
  label->mutable_categorical()->set_number_of_unique_values(3);

  RandomForestBinaryClassificationNumericalFeatures flat_model;
  CHECK_OK(GenericToSpecializedModel(rf_model, &flat_model));

  EXPECT_THAT(FeatureNames(flat_model.features().fixed_length_features()),
              ElementsAre("col_1"));
  EXPECT_THAT(flat_model.features().fixed_length_na_replacement_values(),
              ElementsAre(NumericalOrCategoricalValue::Numerical(4.f)));
  EXPECT_THAT(flat_model.root_offsets, ElementsAre(0));

  EXPECT_EQ(flat_model.nodes.size(), 3);

  EXPECT_EQ(flat_model.nodes[0].right_idx, 2);
  EXPECT_EQ(flat_model.nodes[0].feature_idx, 0);
  EXPECT_NEAR(flat_model.nodes[0].threshold, 2, 0.0001f);

  EXPECT_EQ(flat_model.nodes[1].right_idx, 0);
  EXPECT_EQ(flat_model.nodes[1].feature_idx, 0);
  EXPECT_NEAR(flat_model.nodes[1].threshold, 1, 0.0001);

  EXPECT_EQ(flat_model.nodes[2].right_idx, 0);
  EXPECT_EQ(flat_model.nodes[2].feature_idx, 0);
  EXPECT_NEAR(flat_model.nodes[2].threshold, 0, 0.0001);
}

TEST(SpecializedRandomForestTest,
     BinaryClassificationNumericalOnlyFlatNodePredict) {
  RandomForestBinaryClassificationNumericalFeatures flat_model;
  flat_model.root_offsets.push_back(0);

  dataset::proto::DataSpecification data_spec = PARSE_TEST_PROTO(
      R"pb(
        columns {
          type: NUMERICAL
          name: "test"
          numerical { mean: 1.0 }
        }
      )pb");
  EXPECT_OK(flat_model.mutable_features()->Initialize({0}, data_spec));

  flat_model.nodes.push_back(OneDimensionOutputNumericalFeatureNode::Leaf(
      /*.right_idx =*/2, /*.feature_idx =*/0,
      /*.label (same as threshold) =*/2));
  flat_model.nodes.push_back(OneDimensionOutputNumericalFeatureNode::Leaf(
      /*.right_idx =*/0, /*.feature_idx =*/0, /*.label =*/1));
  flat_model.nodes.push_back(OneDimensionOutputNumericalFeatureNode::Leaf(
      /*.right_idx =*/0, /*.feature_idx =*/0, /*.label =*/0));

  std::vector<float> flat_examples = {1.f, 3.f};
  std::vector<float> predictions;
  Predict(flat_model, flat_examples, 2, &predictions);

  EXPECT_THAT(predictions, ElementsAre(1.f, 0.f));
}

struct AllCompatibleEnginesTestParams {
  const std::string model;
  const std::string dataset;
  const std::unordered_set<std::string> expected_engines;
  const std::string dataset_format = "csv";
};

using AllCompatibleEnginesTest =
    testing::TestWithParam<AllCompatibleEnginesTestParams>;

// Test all the compatible engines. Make sure at least one engine is compatible.
TEST_P(AllCompatibleEnginesTest, Automtac) {
  const auto model = LoadModel(GetParam().model);
  const auto dataset = LoadDataset(model->data_spec(), GetParam().dataset,
                                   GetParam().dataset_format);
  const auto factories = model->ListCompatibleFastEngines();
  CHECK_GE(factories.size(), 1);
  for (const auto& factory : factories) {
    const auto engine = factory->CreateEngine(model.get()).value();
    utils::ExpectEqualPredictions(dataset, *model, *engine);
  }

  CheckCompatibleEngine(*model, GetParam().expected_engines);
}

// Concurrently compiles 100 DF models on 10 threads for each engine.
TEST_P(AllCompatibleEnginesTest, Concurent) {
  const std::unique_ptr<model::AbstractModel> model =
      LoadModel(GetParam().model);
  const dataset::VerticalDataset dataset = LoadDataset(
      model->data_spec(), GetParam().dataset, GetParam().dataset_format);
  const std::vector<std::unique_ptr<model::FastEngineFactory>> factories =
      model->ListCompatibleFastEngines();

  const auto compile_model =
      [model = model.get()](
          const model::FastEngineFactory* factory) -> absl::Status {
    ASSIGN_OR_RETURN(const auto engine, factory->CreateEngine(model));
    // Note: Discard the engine.
    return absl::OkStatus();
  };

  const int num_repetitions = 100;

  for (const auto& factory : factories) {
    utils::concurrency::StreamProcessor<const model::FastEngineFactory*,
                                        absl::Status>
        processor("model compiler", /*num_threads=*/10, compile_model);
    processor.StartWorkers();
    for (int rep_idx = 0; rep_idx < num_repetitions; rep_idx++) {
      processor.Submit(factory.get());
    }
    processor.CloseSubmits();

    for (int rep_idx = 0; rep_idx < num_repetitions; rep_idx++) {
      const absl::optional<absl::Status> result = processor.GetResult();
      ASSERT_TRUE(result.has_value());
      EXPECT_OK(*result);
    }
    processor.JoinAllAndStopThreads();
  }
}

std::unordered_set<std::string> AllRFEngines() {
  return {
      random_forest::kOptPred,
      random_forest::kGeneric,
  };
}

INSTANTIATE_TEST_SUITE_P(
    AllCompatibleEnginesTests, AllCompatibleEnginesTest,
    testing::ValuesIn<AllCompatibleEnginesTestParams>({
        {
            "adult_binary_class_oblique_rf",
            "adult_test.csv",
            {random_forest::kGeneric},
        },
        {
            "adult_binary_class_rf",
            "adult_test.csv",
            {random_forest::kGeneric},
        },
        {"adult_binary_class_rf_32cat", "adult_test.csv", AllRFEngines()},
        {
            "adult_binary_class_rf_discret_numerical",
            "adult_test.csv",
            {random_forest::kGeneric},
        },
        {"adult_binary_class_rf_only_num", "adult_test.csv", AllRFEngines()},
        {
            "iris_multi_class_rf",
            "iris.csv",
            {random_forest::kGeneric},
        },
        {
            "sst_binary_class_rf",
            "sst_binary_test.csv",
            {random_forest::kGeneric},
        },
    }),
    [](const testing::TestParamInfo<AllCompatibleEnginesTest::ParamType>&
           info) {
      return absl::StrCat(
          info.param.model, "_",
          absl::StrReplaceAll(info.param.dataset, {{".", "_"}, {"-", "_"}}));
    });

TEST(AdultBinaryClassRF, ManualNumCat32) {
  const auto model = LoadModel("adult_binary_class_rf_32cat");
  const auto dataset = LoadDataset(model->data_spec(), "adult_test.csv", "csv");

  auto* gbt_model = dynamic_cast<RandomForestModel*>(model.get());
  RandomForestBinaryClassificationNumericalAndCategoricalFeatures engine;
  CHECK_OK(GenericToSpecializedModel(*gbt_model, &engine));

  // TODO Fix test
  utils::ExpectEqualPredictionsOldTemplate<decltype(engine), Predict>(dataset, *model, engine);
}

TEST(AdultBinaryClassRF, ManualNum) {
  const auto model = LoadModel("adult_binary_class_rf_only_num");
  const auto dataset = LoadDataset(model->data_spec(), "adult_test.csv", "csv");

  auto* gbt_model = dynamic_cast<RandomForestModel*>(model.get());
  RandomForestBinaryClassificationNumericalFeatures engine;
  CHECK_OK(GenericToSpecializedModel(*gbt_model, &engine));

  utils::ExpectEqualPredictionsOldTemplate<decltype(engine), Predict>(
      dataset, *model, engine);
}

TEST(IrisMulticlassClassRF, ManualGeneric) {
  const auto model = LoadModel("iris_multi_class_rf");
  const auto dataset = LoadDataset(model->data_spec(), "iris.csv", "csv");

  auto* gbt_model = dynamic_cast<RandomForestModel*>(model.get());
  RandomForestMulticlassClassification engine;
  CHECK_OK(GenericToSpecializedModel(*gbt_model, &engine));

  utils::ExpectEqualPredictionsTemplate<decltype(engine), Predict>(
      dataset, *model, engine);
}

TEST(SimPTECategoricalupliftRF, ManualGeneric) {
  const auto model = LoadModel("sim_pte_categorical_uplift_rf");
  const auto dataset =
      LoadDataset(model->data_spec(), "sim_pte_test.csv", "csv");

  auto* rf_model = dynamic_cast<RandomForestModel*>(model.get());
  RandomForestCategoricalUplift engine;
  CHECK_OK(GenericToSpecializedModel(*rf_model, &engine));

  utils::ExpectEqualPredictionsTemplate<decltype(engine), Predict>(
      dataset, *model, engine);
}

void BuildFullTree(const int d, model::decision_tree::NodeWithChildren* node) {
  if (d <= 0) {
    node->mutable_node()->mutable_classifier()->set_top_value(1.f);
    return;
  }
  node->CreateChildren();
  node->mutable_node()->mutable_condition()->set_attribute(0);
  node->mutable_node()
      ->mutable_condition()
      ->mutable_condition()
      ->mutable_higher_condition()
      ->set_threshold(1.f);
  BuildFullTree(d - 1, node->mutable_pos_child());
  BuildFullTree(d - 1, node->mutable_neg_child());
}

template <typename Engine>
std::unique_ptr<typename Engine::ExampleSet> BuildNonGlobalImputationExamples(
    const Engine& engine) {
  auto examples = absl::make_unique<typename Engine::ExampleSet>(6, engine);

  const auto& fs = engine.features();
  auto feature_b = engine.features().GetNumericalFeatureId("b").value();
  auto feature_c = engine.features().GetNumericalFeatureId("c").value();

  examples->SetNumerical(/*example_idx=*/5, feature_b, /*value=*/0.0f, fs);
  examples->SetNumerical(/*example_idx=*/1, feature_b, /*value=*/0.0f, fs);
  examples->SetNumerical(/*example_idx=*/2, feature_b, /*value=*/0.0f, fs);
  examples->SetNumerical(/*example_idx=*/3, feature_b, /*value=*/2.0f, fs);
  examples->SetNumerical(/*example_idx=*/4, feature_b, /*value=*/2.0f, fs);
  examples->SetNumerical(/*example_idx=*/0, feature_b, /*value=*/2.0f, fs);

  examples->SetNumerical(/*example_idx=*/5, feature_c, /*value=*/0.0f, fs);
  examples->SetNumerical(/*example_idx=*/1, feature_c, /*value=*/3.0f, fs);
  examples->SetMissingNumerical(/*example_idx=*/2, feature_c, fs);
  examples->SetNumerical(/*example_idx=*/3, feature_c, /*value=*/0.0f, fs);
  examples->SetNumerical(/*example_idx=*/4, feature_c, /*value=*/3.0f, fs);
  examples->SetMissingNumerical(/*example_idx=*/0, feature_c, fs);
  return examples;
}

}  // namespace
}  // namespace decision_forest
}  // namespace serving
}  // namespace yggdrasil_decision_forests
