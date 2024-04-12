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

add_library(
  status_macros
  STATIC
  status_macros.h
  status_macros_default.h
)
target_include_directories(status_macros PRIVATE ${absl_SOURCE_DIR})
target_link_libraries(
  status_macros
  PRIVATE
  absl::status
  absl::statusor
)

add_library(
  regex
  STATIC
  regex.cc
)
target_include_directories(regex PRIVATE ${absl_SOURCE_DIR})
target_link_libraries(
  regex
  PRIVATE
  absl::strings
)

enable_testing()
add_executable(
  utils_tests 
  logging_test.cc
  adaptive_work_test.cc
  status_macros_test.cc
  regex_test.cc
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
  status_macros
  regex
  GTest::gtest_main GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(utils_tests)
