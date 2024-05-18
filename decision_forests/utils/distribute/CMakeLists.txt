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
add_library(utils_distribute ALIAS distribute)

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
add_library(utils_toy_worker ALIAS toy_worker)

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
add_library(utils_distribute_test_utils ALIAS distribute_test_utils)

# Tests
file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_executable(
  utils_distribute_tests
  ${test_SRC_FILES}
)
target_include_directories(
  utils_distribute_tests
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  utils_distribute_tests
  PRIVATE
# this objects
  utils_distribute
  utils_multi_thread
  utils_toy_worker
  utils_distribute_test_utils
# other local objects
  utils_proto
  utils_registration
  utils_filesystem
# third_party objects
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

