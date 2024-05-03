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

#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"
#include "learner/abstract_learner.pb.h"
#include "learner/hyperparameters_optimizer/hyperparameters_optimizer.h"
#include "learner/random_forest/random_forest.pb.h"
#include "metric/metric.h"
#include "metric/metric.pb.h"
#include "model/abstract_model.h"
#include "model/abstract_model.pb.h"
#include "utils/filesystem.h"
#include "utils/test.h"
#include "e2e_test_utils/test_utils.h"

namespace yggdrasil_decision_forests {
namespace model {
namespace random_forest {
namespace {

class AutotunedRandomForestOnAdult : public utils::TrainAndTestTester {
  void SetUp() override {
    train_config_ = PARSE_TEST_PROTO(R"pb(
      task: CLASSIFICATION
      learner: "HYPERPARAMETER_OPTIMIZER"
      label: "income"

      [yggdrasil_decision_forests.model.hyperparameters_optimizer_v2.proto
           .hyperparameters_optimizer_config] {

        optimizer {
          optimizer_key: "RANDOM"
          parallel_trials: 10
          [yggdrasil_decision_forests.model.hyperparameters_optimizer_v2.proto
               .random] { num_trials: 10 }
        }

        base_learner {
          learner: "RANDOM_FOREST"
          [yggdrasil_decision_forests.model.random_forest.proto
               .random_forest_config] { num_trees: 50 }
        }

        base_learner_deployment { num_threads: 3 }

        predefined_search_space {}
      }
    )pb");

    train_config_.set_learner(
        hyperparameters_optimizer_v2::HyperParameterOptimizerLearner::
            kRegisteredName);
    train_config_.set_task(model::proto::Task::CLASSIFICATION);
    train_config_.set_label("income");
    train_config_.add_features(".*");
    dataset_filename_ = "adult.csv";

    deployment_config_.set_cache_path(
        file::JoinPath(test::TmpDirectory(), "working_directory"));
  }
};

TEST_F(AutotunedRandomForestOnAdult, RandomTuner_MemoryDataset_LocalTraining) {
  TrainAndEvaluateModel();
  EXPECT_GE(metric::Accuracy(evaluation_), 0.86);
  EXPECT_EQ(model_->hyperparameter_optimizer_logs()->steps_size(), 10);
}

}  // namespace
}  // namespace random_forest
}  // namespace model
}  // namespace yggdrasil_decision_forests
