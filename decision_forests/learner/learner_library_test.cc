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

#include "learner_library.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "utils/test.h"

namespace yggdrasil_decision_forests {
namespace model {
namespace {

using test::EqualsProto;

TEST(ModelLibrary, CreateAllLearners) {
  for (const auto& learner_name : AllRegisteredLearners()) {
    YDF_LOG(INFO) << learner_name;
    std::unique_ptr<AbstractLearner> learner;
    proto::TrainingConfig train_config;
    train_config.set_label("my_label");
    train_config.set_learner(learner_name);
    EXPECT_OK(GetLearner(train_config, &learner));
  }
}

}  // namespace
}  // namespace model
}  // namespace yggdrasil_decision_forests
