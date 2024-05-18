add_subdirectory(decision_forest)

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
  absl::strings
  absl::status
  absl::statusor
  protobuf::libprotoc
)
add_library(serving_example_set ALIAS example_set)

add_library(
  fast_engine_registration
  STATIC
  fast_engine_registration.cc
)
target_include_directories(
  fast_engine_registration
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  fast_engine_registration
  PRIVATE
  serving_register_engines
)
add_library(serving_fast_engine_registration ALIAS fast_engine_registration)

# Tests
if(blom_BUILD_TESTS)
  file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
  add_executable(
    serving_tests
    ${test_SRC_FILES}
  )
  target_include_directories(
    serving_tests
    PRIVATE
    ${absl_SOURCE_DIR}
    ${googletest_SOURCE_DIR}
    ${protobuf_SOURCE_DIR}/src
    ${farmhash_SOURCE_DIR}/src
    ${PROTOC_GENERATED_SOURCE_DIR}
  )
  target_link_libraries(
    serving_tests
    PRIVATE
    dataset_proto
    learner_proto
    metric_ranking_utils
    metric_metric
    model_abstract_model
    model_metadata
    serving_example_set
    protobuf::libprotoc
    GTest::gtest_main
    GTest::gmock_main
  )
  include(GoogleTest)
  gtest_discover_tests(serving_tests)
endif()

