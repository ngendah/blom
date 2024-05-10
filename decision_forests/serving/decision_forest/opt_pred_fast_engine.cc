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

#include "opt_pred_fast_engine.h"
#include "register_engines.h"
#include "model/random_forest/random_forest.h"

namespace yggdrasil_decision_forests{
namespace model {

std::string OptPredFastEngineFactory::name() const {
  return serving::random_forest::kOptPred;
}

bool OptPredFastEngineFactory::IsCompatible(const AbstractModel* const model) const {
  using SourceModel = random_forest::RandomForestModel;
  auto* rf_model = dynamic_cast<const SourceModel*>(model);
  // This implementation is the most generic and least efficient engine.
  if (rf_model == nullptr) {
    return false;
  }
  if (!rf_model->CheckStructure(
          decision_tree::CheckStructureOptions::GlobalImputation())) {
    return false;
  }

  for (const auto& src_tree : rf_model->decision_trees()) {
    if (src_tree->NumLeafs() > std::numeric_limits<uint16_t>::max()) {
      return false;
    }
  }

  if (!CheckAllFeatureForOptModel(model)) {
    return false;
  }

  if (!CheckAllConditionsForOptModels(rf_model->decision_trees())) {
    return false;
  }

  switch (rf_model->task()) {
    case proto::CLASSIFICATION:
      return rf_model->label_col_spec()
                 .categorical()
                 .number_of_unique_values() == 3;
    case proto::REGRESSION:
    case proto::RANKING:
      return true;
    default:
      return false;
  }
}

std::vector<std::string> OptPredFastEngineFactory::IsBetterThan() const {
  return {serving::random_forest::kGeneric};
}

absl::StatusOr<std::unique_ptr<serving::FastEngine>> OptPredFastEngineFactory::CreateEngine(
    const AbstractModel* const model) const {
  using SourceModel = random_forest::RandomForestModel;
  auto* rf_model = dynamic_cast<const SourceModel*>(model);
  if (!rf_model) {
    return absl::InvalidArgumentError("The model is not a RF.");
  }

  if (!rf_model->CheckStructure(
          decision_tree::CheckStructureOptions::GlobalImputation())) {
    return NoGlobalImputationError("OptPredFastEngineFactory");
  }

  switch (rf_model->task()) {
    case model::proto::CLASSIFICATION: {
      auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
          serving::decision_forest::
              RandomForestBinaryClassificationNumericalAndCategoricalFeatures,
          serving::decision_forest::PredictWithExampleSet>>();
      RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
      return engine;
    }

    case model::proto::REGRESSION: {
      auto engine = absl::make_unique<serving::ExampleSetModelWrapper<
          serving::decision_forest::
              RandomForestRegressionNumericalAndCategorical,
          serving::decision_forest::PredictWithExampleSet>>();
      RETURN_IF_ERROR(engine->LoadModel<SourceModel>(*rf_model));
      return engine;
    }

    default:
      return absl::InvalidArgumentError("Non supported RF model");
  }
}


} // namespace model
} // namespace yggdrasil_decision_forests
