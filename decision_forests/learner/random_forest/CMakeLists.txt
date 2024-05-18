add_library(
  learner_random_forest
  STATIC
  random_forest.cc
  random_forest_hparams_templates.cc
)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(learner_random_forest PRIVATE -Wno-return-type -Wno-non-template-friend -Wno-attributes)
endif()
target_include_directories(
  learner_random_forest
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_random_forest
  PRIVATE
  learner_proto
  hyperparameters_optimizer_proto
  model_proto
  model_decision_tree_proto
  dataset_vertical_dataset
  learner_decision_tree_training
  learner_decision_tree_generic_parameters
  metric_metric
  model_decision_tree
  model_random_forest
  utils_adaptive_work
  utils_concurrency
  utils_feature_importance
  utils_logging
  utils_usage
  e2e_test_utils
  absl::strings
  absl::status
  absl::statusor
  protobuf::libprotoc
  farmhash::farmhash
)


# Tests

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_executable(
  learner_random_forest_tests
  ${test_SRC_FILES}
)
target_include_directories(
  learner_random_forest_tests
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_random_forest_tests
  PRIVATE
  hyperparameters_optimizer_proto
  learner_proto
  model_decision_tree_proto
  dataset_vertical_dataset
  learner_decision_tree_training
  learner_hyperparameters_optimizer
  learner_library
  learner_random_forest
  metric_ranking_utils
  metric_metric
  model_abstract_model
  utils_filesystem
  utils_logging
  utils_testing_utils
  protobuf::libprotoc
  GTest::gtest_main
  GTest::gmock_main
)
if(CMAKE_HOST_UNIX OR CMAKE_HOST_WIN32)
  include(GoogleTest)
  gtest_discover_tests(learner_random_forest_tests)
endif()

