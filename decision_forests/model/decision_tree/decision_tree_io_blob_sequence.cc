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

#include "decision_tree_io_blob_sequence.h"
#include "utils/sharded_io_blob_sequence.h"

namespace yggdrasil_decision_forests {
namespace model {
namespace decision_tree {

std::unique_ptr<utils::ShardedReader<proto::Node>> BlobSequenceFormat::CreateReader()
    const {
  return absl::make_unique<utils::BlobSequenceShardedReader<proto::Node>>();
};

std::unique_ptr<utils::ShardedWriter<proto::Node>> BlobSequenceFormat::CreateWriter()
    const {
  return absl::make_unique<utils::BlobSequenceShardedWriter<proto::Node>>();
};

}  // namespace decision_tree
}  // namespace model
}  // namespace yggdrasil_decision_forests
