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

#include "decision_tree_io_interface.h"

#include "model/decision_tree/decision_tree.pb.h"
#include "utils/sharded_io.h"
#include "utils/sharded_io_blob_sequence.h"

namespace yggdrasil_decision_forests {
namespace model {
namespace decision_tree {

// The BlobSequence format is a minimal container format managed by Yggdrasil
// and without external dependencies. This is the recommended format for Open
// Source.
class BlobSequenceFormat : public AbstractFormat {
 public:
  ~BlobSequenceFormat() override = default;

  std::unique_ptr<utils::ShardedReader<proto::Node>> CreateReader()
      const override {
    return absl::make_unique<utils::BlobSequenceShardedReader<proto::Node>>();
  };

  std::unique_ptr<utils::ShardedWriter<proto::Node>> CreateWriter()
      const override {
    return absl::make_unique<utils::BlobSequenceShardedWriter<proto::Node>>();
  };
};
REGISTER_AbstractFormat(BlobSequenceFormat, "BLOB_SEQUENCE");

}  // namespace decision_tree
}  // namespace model
}  // namespace yggdrasil_decision_forests
