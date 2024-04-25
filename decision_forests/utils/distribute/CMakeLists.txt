add_subdirectory(implementations)

add_library(
  distribute
  STATIC
  core.cc
  distribute.cc
  utils.cc
)
target_include_directories(
  distribute
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  distribute
  PRIVATE
  utils_proto
  absl::status
  absl::statusor
  absl::strings
  protobuf::libprotoc
)

add_library(
  toy_worker
  STATIC
  toy_worker.cc
)
target_include_directories(
  toy_worker
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  toy_worker
  PRIVATE
  distribute
  absl::synchronization
  protobuf::libprotoc
)

add_library(
  distribute_test_utils
  STATIC
  test_utils.cc
)
target_include_directories(
  distribute_test_utils
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  distribute_test_utils
  PRIVATE
  distribute
  concurrency
  absl::synchronization
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  utils_distribute_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  utils_distribute_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  utils_distribute_tests_obj
  PRIVATE
# this objects
  distribute
  multi_thread
  toy_worker
  distribute_test_utils
# other local objects
  utils_proto
  registration
  filesystem
# third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

