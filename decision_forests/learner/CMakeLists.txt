add_subdirectory(decision_tree)
add_subdirectory(cart)

add_library(
  abstract_learner
  STATIC
  abstract_learner.cc
)
target_include_directories(
  abstract_learner
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  abstract_learner
  PRIVATE
  model_proto
  dataset_proto
  dataset_data_spec 
  dataset_vertical_dataset
  dataset_weight
  dataset_types
  metric_metric
  metric_ranking_utils
  model_abstract_model
  model_metadata
  fold_generator
  utils_concurrency
  utils_logging
  utils_hyper_parameters
  absl::status
  absl::statusor
  absl::strings
  absl::time
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(learner_abstract_learner ALIAS abstract_learner)

add_library(
  learner_library
  STATIC
  learner_library.cc
)
target_include_directories(
  learner_library
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_library
  PRIVATE
  learner_proto
  absl::status
  absl::statusor
  absl::strings
  absl::time
  farmhash::farmhash
  protobuf::libprotoc
)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  learner_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  learner_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_tests_obj
  PRIVATE
  dataset_proto
  learner_proto
  dataset_data_spec 
  dataset_vertical_dataset
  metric_metric
  model_abstract_model
  learner_abstract_learner
  learner_library
  utils_logging
  utils_testing_utils
  # third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

