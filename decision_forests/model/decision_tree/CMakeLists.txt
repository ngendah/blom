add_library(
  builder
  STATIC
  builder.cc
)
target_include_directories(
  builder
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  builder
  PRIVATE
  model_proto
  dataset_proto
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(model_decision_tree_builder ALIAS builder)

add_library(
  decision_tree
  STATIC
  decision_tree.cc
)
target_include_directories(
  decision_tree
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  decision_tree
  PRIVATE
  model_proto
  dataset_proto
  utils_proto
  dataset_data_spec
  dataset_vertical_dataset
  model_decision_tree_builder
  utils_bitmap
  utils_logging
  utils_sharded_io
  utils_status_macros
  absl::strings
  absl::status
  absl::statusor
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(model_decision_tree ALIAS decision_tree)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  model_decision_tree_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  model_decision_tree_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  model_decision_tree_tests_obj
  PRIVATE
  model_proto
  dataset_proto
  model_decision_tree_builder
  model_decision_tree
  dataset_data_spec
  dataset_data_spec_inference
  dataset_vertical_dataset
  utils_filesystem
  utils_logging
  utils_status_macros
  utils_testing_utils
  # third_party objects
  protobuf::libprotoc
  farmhash::farmhash
  GTest::gtest_main GTest::gmock_main
)

