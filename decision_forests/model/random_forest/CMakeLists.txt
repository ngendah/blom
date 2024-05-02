add_library(
  random_forest
  STATIC
  random_forest.cc
)
target_include_directories(
  random_forest
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  random_forest
  PRIVATE
  dataset_proto
  model_proto
  dataset_vertical_dataset
  model_decision_tree_io
  model_decision_tree_structure_analysis
  utils_distribution
  utils_plot
  utils_blob_sequence
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(model_decision_tree_random_forest ALIAS random_forest)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  model_random_forest_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  model_random_forest_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  model_random_forest_tests_obj
  PRIVATE
  model_proto
  dataset_proto
  model_decision_tree_builder
  model_decision_tree
  dataset_vertical_dataset
  utils_logging
  utils_status_macros
  utils_testing_utils
  # third_party objects
  protobuf::libprotoc
  farmhash::farmhash
  GTest::gtest_main GTest::gmock_main
)

