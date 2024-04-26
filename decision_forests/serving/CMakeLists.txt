add_library(
  example_set
  STATIC
  example_set.cc
)
target_include_directories(
  example_set
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  example_set
  PRIVATE
  dataset_data_spec 
  dataset_vertical_dataset
  utils_logging
  utils_status_macros
  absl::strings
  absl::status
  absl::statusor
  protobuf::libprotoc
)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  serving_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  serving_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  serving_tests_obj
  PRIVATE
# other project objects
  dataset_proto
  learner_proto
# this objects
  example_set
  model_metadata
  metric_ranking_utils
  metric_metric
  model_abstract_model
  # third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

