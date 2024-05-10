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

// Inference engine names for decision forest models.
//
#ifndef YGGDRASIL_DECISION_FORESTS_SERVING_REGISTER_ENGINE_DECISION_FOREST_H_
#define YGGDRASIL_DECISION_FORESTS_SERVING_REGISTER_ENGINE_DECISION_FOREST_H_

#include <string>

#include "decision_forest.h"

#include "absl/status/statusor.h"
#include "dataset/data_spec.pb.h"
#include "serving/example_set_model_wrapper.h"

namespace yggdrasil_decision_forests {

namespace serving {
namespace random_forest {
constexpr char kGeneric[] = "RandomForestGeneric";
constexpr char kOptPred[] = "RandomForestOptPred";
}  // namespace random_forest
} // namespace serving

namespace model {

absl::Status NoGlobalImputationError(const absl::string_view class_name);

// Maximum number of nodes in any tree.
int64_t MaxNumberOfNodesPerTree(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>& trees);

// Checks that all the features return true through "check_feature".
bool CheckAllFeatures(
    const AbstractModel* const model,
    const std::function<bool(const dataset::proto::Column&)>& check_feature);

// Checks that all the features are compatible for a "Opt" type model. Those
// models only support numerical and categorical features with arity<32.
bool CheckAllFeatureForOptModel(const AbstractModel* const model);

// Checks that all the conditions return true through "check_condition".
bool CheckAllConditions(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>&
        decision_trees,
    std::function<bool(const model::decision_tree::proto::Condition&)>
        check_condition);

// Checks that all the conditions are compatible for "Opt" type models.
bool CheckAllConditionsForOptModels(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>&
        decision_trees);

// Checks that all the conditions are compatible for "QuickScorerExtended" type
// models.
bool AllConditionsCompatibleQuickScorerExtendedModels(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>&
        decision_trees);

} // namespace model
} // namespace yggdrasil_decision_forests
#endif  // YGGDRASIL_DECISION_FORESTS_SERVING_REGISTER_ENGINE_DECISION_FOREST_H_
