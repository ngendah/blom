/*
 * Copyright 2024 Ngenda Henry.
 *
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

#include "fast_engine_registration.h"
#include "serving/decision_forest/generic_fast_engine.h"
#include "serving/decision_forest/opt_pred_fast_engine.h"

namespace yggdrasil_decision_forests {
namespace serving {

std::vector<std::string> EnsureFastEngineRegistration() {
  return {
    yggdrasil_decision_forests::model::GenericFastEngineFactory::kRegisteredName,
    yggdrasil_decision_forests::model::OptPredFastEngineFactory::kRegisteredName,
  };
}

}
}

