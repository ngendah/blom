add_library(
  generic_worker
  STATIC
  generic_worker.cc
)
target_include_directories(
  generic_worker
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  generic_worker
  PRIVATE
  learner_generic_worker_proto
  dataset_weight
  learner_abstract_learner
  learner_library
  model_library
  utils_filesystem
  utils_protobuf
  utils_status_macros
  utils_distribute
)
add_library(learner_generic_worker ALIAS generic_worker)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  learner_generic_worker_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  learner_generic_worker_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_generic_worker_tests_obj
  PRIVATE
  learner_generic_worker_proto
  dataset_data_spec_inference
  metric_ranking_utils
  metric_uplift
  model_library
  learner_generic_worker
  utils_distribute
  utils_filesystem
  utils_logging
  utils_testing_utils
  # third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

