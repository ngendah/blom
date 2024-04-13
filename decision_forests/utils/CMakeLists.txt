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
add_custom_command(
  OUTPUT distribution.pb.h distribution.pb.cc
  COMMAND ${protobuf_BINARY_DIR}/protoc -I=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/distribution.proto
  DEPENDS ${protobuf_BINARY_DIR}/protoc ${CMAKE_CURRENT_SOURCE_DIR}/distribution.proto
  VERBATIM
)
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
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  utils_tests
# utils targets
  logging
  adaptive_work
  status_macros
  regex
# third_party targets
  GTest::gtest_main GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(utils_tests)

