add_library(
  optimizers_random
  STATIC
  random.cc
)
target_include_directories(
  optimizers_random
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  optimizers_random
  PRIVATE
  metric_proto
  learner_proto
  hyperparameters_optimizer_proto
  utils_registration
  absl::status
  absl::statusor
  farmhash::farmhash
  protobuf::libprotoc
)
add_library(learner_optimizers_random ALIAS optimizers_random)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  learner_optimizers_random_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  learner_optimizers_random_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_optimizers_random_tests_obj
  PRIVATE
  learner_proto
  model_proto
  metric_proto
  learner_optimizers_random
  utils_logging
  utils_testing_utils
  # third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

