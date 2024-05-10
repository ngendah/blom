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

// Registers generic engines for decision forest models.
//
#include "register_engines.h"

namespace yggdrasil_decision_forests {
namespace model {

absl::Status NoGlobalImputationError(const absl::string_view class_name) {
  return absl::InvalidArgumentError(absl::StrCat(
      "The inference engine \"", class_name,
      "\" only support models trained with "
      "missing_value_policy=GLOBAL_IMPUTATION. This model was trained with "
      "another type of imputation for missing values"));
}

int64_t MaxNumberOfNodesPerTree(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>& trees) {
  int64_t max_num_nodes = 0;
  for (const auto& tree : trees) {
    max_num_nodes = std::max(max_num_nodes, tree->NumNodes());
  }
  return max_num_nodes;
}

bool CheckAllFeatures(
    const AbstractModel* const model,
    const std::function<bool(const dataset::proto::Column&)>& check_feature) {
  for (const auto feature_idx : model->input_features()) {
    const auto& feature = model->data_spec().columns(feature_idx);
    if (!check_feature(feature)) {
      return false;
    }
  }
  return true;
}

bool CheckAllFeatureForOptModel(const AbstractModel* const model) {
  const auto check_feature = [](const dataset::proto::Column& feature) {
    switch (feature.type()) {
      case dataset::proto::ColumnType::NUMERICAL:
        break;
      case dataset::proto::ColumnType::CATEGORICAL:
        if (feature.categorical().number_of_unique_values() > 32) {
          return false;
        }
        break;
      default:
        return false;
    }
    return true;
  };

  return CheckAllFeatures(model, check_feature);
}

bool CheckAllConditions(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>&
        decision_trees,
    std::function<bool(const model::decision_tree::proto::Condition&)>
        check_condition) {
  for (const auto& tree : decision_trees) {
    bool valid = true;
    tree->IterateOnNodes([&](const model::decision_tree::NodeWithChildren& node,
                             const int depth) {
      if (!node.IsLeaf()) {
        valid &= check_condition(node.node().condition().condition());
      }
    });
    if (!valid) {
      return false;
    }
  }
  return true;
}

bool CheckAllConditionsForOptModels(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>&
        decision_trees) {
  // Follow "SetNonLeafNode" in serving/decision_forest/decision_forest.cc.
  const auto check_condition =
      [](const model::decision_tree::proto::Condition& condition) {
        switch (condition.type_case()) {
          case model::decision_tree::proto::Condition::kHigherCondition:
          case model::decision_tree::proto::Condition::kTrueValueCondition:
          case model::decision_tree::proto::Condition::kContainsBitmapCondition:
          case model::decision_tree::proto::Condition::kContainsCondition:
            return true;
          default:
            return false;
        }
      };
  return CheckAllConditions(decision_trees, check_condition);
}

bool AllConditionsCompatibleQuickScorerExtendedModels(
    const std::vector<std::unique_ptr<decision_tree::DecisionTree>>&
        decision_trees) {
  // Follow "FillQuickScorerNode" in
  // serving/decision_forest/quick_scorer_extended.cc.
  const auto check_condition = [](const model::decision_tree::proto::Condition&
                                      condition) {
    switch (condition.type_case()) {
      case model::decision_tree::proto::Condition::kHigherCondition:
      case model::decision_tree::proto::Condition::kDiscretizedHigherCondition:
      case model::decision_tree::proto::Condition::kTrueValueCondition:
      case model::decision_tree::proto::Condition::kContainsCondition:
      case model::decision_tree::proto::Condition::kContainsBitmapCondition:
        return true;
      default:
        return false;
    }
  };
  return CheckAllConditions(decision_trees, check_condition);
}

}  // namespace model
}  // namespace yggdrasil_decision_forests
