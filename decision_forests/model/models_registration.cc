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
#include "models_registration.h"

#include "model/random_forest/random_forest.h"
#include "model/decision_tree/decision_tree_io_blob_sequence.h"

namespace yggdrasil_decision_forests {
namespace model {

std::vector<std::string> EnsureModelsRegistration() {
  return { random_forest::RandomForestModel:: kRegisteredName };
}

std::vector<std::string> EnsureModelsIORegistration() {
  return {
    decision_tree::BlobSequenceFormat::kRegisteredName
  };
}

}
}

