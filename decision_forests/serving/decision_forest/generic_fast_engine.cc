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

#include "generic_fast_engine.h"
#include "register_engines.h"
#include "model/random_forest/random_forest.h"

namespace  yggdrasil_decision_forests {
namespace  model {

std::string GenericFastEngineFactory::name() const {
  return serving::random_forest::kGeneric;
}

bool GenericFastEngineFactory::IsCompatible(const AbstractModel* const model) const {
  using SourceModel = random_forest::RandomForestModel;
  auto* rf_model = dynamic_cast<const SourceModel*>(model);
  // This implementation is the most generic and least efficient engine.
  if (rf_model == nullptr) {
    return false;
  }
  return rf_model->CheckStructure({/*.global_imputation_is_higher =*/false});
}

std::vector<std::string> GenericFastEngineFactory::IsBetterThan() const {
  return {};
}

absl::StatusOr<std::unique_ptr<serving::FastEngine>> GenericFastEngineFactory::CreateEngine(
    const AbstractModel* const model) const {
  using SourceModel = random_forest::RandomForestModel;
  auto* rf_model = dynamic_cast<const SourceModel*>(model);
  if (!rf_model) {
    return absl::InvalidArgumentError("The model is not a RF.");
  }

  if (!rf_model->CheckStructure({/*.global_imputation_is_higher =*/false})) {
    return NoGlobalImputationError("GenericFastEngineFactory");
  }

  const bool need_uint32_node_index =
      MaxNumberOfNodesPerTree(rf_model->decision_trees()) >=
      std::numeric_limits<uint16_t>::max();

  switch (rf_model->task())
  case model::proto::CLASSIFICATION:
    if (rf_model->label_col_spec().categorical().number_of_unique_values() ==
        3) {
      // Binary classification.
      if (need_uint32_node_index) {
        auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
            serving::decision_forest::GenericRandomForestBinaryClassification<
                uint32_t>,
            serving::decision_forest::Predict>>();
        RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
        return engine;
      } else {
        auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
            serving::decision_forest::GenericRandomForestBinaryClassification<
                uint16_t>,
            serving::decision_forest::Predict>>();
        RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
        return engine;
      }
    } else {
      // Multi-class classification.
      if (need_uint32_node_index) {
        auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
            serving::decision_forest::
                GenericRandomForestMulticlassClassification<uint32_t>,
            serving::decision_forest::Predict>>();
        RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
        return engine;
      } else {
        auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
            serving::decision_forest::
                GenericRandomForestMulticlassClassification<uint16_t>,
            serving::decision_forest::Predict>>();
        RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
        return engine;
      }

      case model::proto::REGRESSION:
        if (need_uint32_node_index) {
          auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
              serving::decision_forest::GenericRandomForestRegression<
                  uint32_t>,
              serving::decision_forest::Predict>>();
          RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
          return engine;
        } else {
          auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
              serving::decision_forest::GenericRandomForestRegression<
                  uint16_t>,
              serving::decision_forest::Predict>>();
          RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
          return engine;
        }

      case model::proto::CATEGORICAL_UPLIFT:
        if (need_uint32_node_index) {
          auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
              serving::decision_forest::GenericRandomForestCategoricalUplift<
                  uint32_t>,
              serving::decision_forest::Predict>>();
          RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
          return engine;
        } else {
          auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
              serving::decision_forest::GenericRandomForestCategoricalUplift<
                  uint16_t>,
              serving::decision_forest::Predict>>();
          RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
          return engine;
        }

      case model::proto::NUMERICAL_UPLIFT:
        if (need_uint32_node_index) {
          auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
              serving::decision_forest::GenericRandomForestNumericalUplift<
                  uint32_t>,
              serving::decision_forest::Predict>>();
          RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
          return engine;
        } else {
          auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
              serving::decision_forest::GenericRandomForestNumericalUplift<
                  uint16_t>,
              serving::decision_forest::Predict>>();
          RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
          return engine;
        }

      default:
        return absl::InvalidArgumentError("Non supported RF model");
    }
}

} // namespace model
} // namespace yggdrasil_decision_forests
