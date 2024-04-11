add_library(
  logging
  STATIC
  logging_default.cc
)
target_include_directories(logging PRIVATE ${absl_SOURCE_DIR})
target_link_libraries(
  logging
  PRIVATE
  absl::flags
  absl::flags_commandlineflag
  absl::flags_parse
  absl::flags_usage
  absl::strings
)

add_library(
  adaptive_work
  STATIC
  adaptive_work.cc
)
target_include_directories(adaptive_work PRIVATE ${absl_SOURCE_DIR})
target_link_libraries(
  adaptive_work
  PRIVATE
  absl::flags
  absl::flags_commandlineflag
  absl::flags_parse
  absl::flags_usage
  absl::status
  absl::strings
  absl::synchronization
  absl::time
)


enable_testing()
add_executable(
  utils_tests 
  logging_test.cc
  adaptive_work_test.cc
)
target_include_directories(
  utils_tests
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
)
target_link_libraries(
  utils_tests
  logging
  adaptive_work
  GTest::gtest_main GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(utils_tests)
