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

#ifndef YGGDRASIL_DECISION_FORESTS_SERVING_OPT_PRED_FAST_ENGINE_H_
#define YGGDRASIL_DECISION_FORESTS_SERVING_OPT_PRED_FAST_ENGINE_H_

#include "model/abstract_model.h"
#include "model/fast_engine_factory.h"
#include "serving/fast_engine.h"

namespace yggdrasil_decision_forests {
namespace model {

class OptPredFastEngineFactory : public FastEngineFactory {
 public:
  static constexpr char kRegisteredName[] = "RandomForestOptPred";

  std::string name() const override;

  bool IsCompatible(const model::AbstractModel* const model) const override;

  std::vector<std::string> IsBetterThan() const override;

  absl::StatusOr<std::unique_ptr<serving::FastEngine>> CreateEngine(
      const model::AbstractModel* const model) const override;
};

REGISTER_FastEngineFactory(OptPredFastEngineFactory,
                           OptPredFastEngineFactory::kRegisteredName);

} // namespace model
} // namespace yggdrasil_decision_forests
#endif // YGGDRASIL_DECISION_FORESTS_SERVING_OPT_PRED_FAST_ENGINE_H_
