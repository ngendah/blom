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
  metadata
  dataset_weight
  metric
  ranking_utils
  dataset_types
  abstract_model
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
# other project objects
  dataset_proto
  learner_proto
  dataset_data_spec 
  dataset_vertical_dataset
  metric
  abstract_model
  utils_logging
# this objects
  abstract_learner
  # third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

