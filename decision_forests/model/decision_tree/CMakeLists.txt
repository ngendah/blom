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
  dataset_proto
  model_decision_tree_proto
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

add_library(
  decision_tree_io
  STATIC
  decision_tree_io.cc
)
target_include_directories(
  decision_tree_io
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  decision_tree_io
  PRIVATE
  dataset_proto
  model_decision_tree_proto
  utils_bytestream
  utils_filesystem
  utils_protobuf
  utils_sharded_io
  utils_status_macros
  absl::strings
  absl::status
  absl::statusor
)
add_library(model_decision_tree_io ALIAS decision_tree_io)

add_library(
  decision_tree_io_blob_sequence
  STATIC
  decision_tree_io_blob_sequence.cc
)
target_include_directories(
  decision_tree_io_blob_sequence
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  decision_tree_io_blob_sequence
  PRIVATE
  model_proto
  utils_bytestream
  utils_filesystem
  utils_protobuf
  utils_sharded_io
  utils_status_macros
  absl::strings
  absl::status
  absl::statusor
)
add_library(model_decision_tree_io_blob_sequence ALIAS decision_tree_io_blob_sequence)

add_library(
  structure_analysis
  STATIC
  structure_analysis.cc
)
target_include_directories(
  structure_analysis
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  structure_analysis
  PRIVATE
  model_proto
  utils_logging
  model_decision_tree
  absl::strings
  absl::status
  absl::statusor
)
add_library(model_decision_tree_structure_analysis ALIAS structure_analysis)


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
  dataset_proto
  model_decision_tree_proto
  model_decision_tree_builder
  model_decision_tree
  dataset_data_spec
  dataset_data_spec_inference
  dataset_library
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

