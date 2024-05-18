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
  model_random_forest_proto
  dataset_vertical_dataset
  model_decision_tree_io
  model_decision_tree_structure_analysis
  utils_blob_sequence
  utils_distribution
  utils_plot
  utils_usage
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(model_random_forest ALIAS random_forest)
# TODO remove and replace instances by above library
add_library(model_decision_tree_random_forest ALIAS random_forest)

# Tests

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_executable(
  model_random_forest_tests
  ${test_SRC_FILES}
)
target_include_directories(
  model_random_forest_tests
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  model_random_forest_tests
  PRIVATE
  model_random_forest_proto
  dataset_vertical_dataset
  model_decision_tree
  model_decision_tree_builder
  model_model_library
  model_random_forest
  utils_logging
  utils_testing_utils
  protobuf::libprotoc
  farmhash::farmhash
  GTest::gtest_main
  GTest::gmock_main
)
if(CMAKE_HOST_UNIX OR CMAKE_HOST_WIN32)
  include(GoogleTest)
  gtest_discover_tests(model_random_forest_tests)
endif()
