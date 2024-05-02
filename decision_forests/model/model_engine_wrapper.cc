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

#include "model_engine_wrapper.h"

#include <vector>

#include "absl/status/status.h"
#include "dataset/example.pb.h"
#include "dataset/vertical_dataset.h"
#include "model/prediction.pb.h"
#include "serving/example_set.h"
#include "utils/logging.h"

namespace yggdrasil_decision_forests {
namespace model {

constexpr char EngineWrapperModel::kRegisteredName[];

void EngineWrapperModel::Predict(const dataset::VerticalDataset& dataset,
                                 dataset::VerticalDataset::row_t row_idx,
                                 model::proto::Prediction* prediction) const {
  const auto fast_example = engine_->AllocateExamples(1);
  CHECK_OK(CopyVerticalDatasetToAbstractExampleSet(
      dataset, row_idx, row_idx + 1, engine_->features(), fast_example.get()));
  std::vector<float> fast_predictions;
  engine_->Predict(*fast_example, 1, &fast_predictions);
  FloatToProtoPrediction(fast_predictions, 0, task_,
                         engine_->NumPredictionDimension(), prediction);
}

void EngineWrapperModel::Predict(const dataset::proto::Example& example,
                                 model::proto::Prediction* prediction) const {
  const auto fast_example = engine_->AllocateExamples(1);
  CHECK_OK(fast_example->FromProtoExample(example, 0, engine_->features()));
  std::vector<float> fast_predictions;
  engine_->Predict(*fast_example, 1, &fast_predictions);
  FloatToProtoPrediction(fast_predictions, 0, task_,
                         engine_->NumPredictionDimension(), prediction);
}

}  // namespace model
}  // namespace yggdrasil_decision_forests
