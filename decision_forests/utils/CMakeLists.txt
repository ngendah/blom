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

add_library(
  protobuf
  STATIC
  protobuf.cc
)
target_include_directories(
  protobuf
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  protobuf
  PRIVATE
  logging
  absl::status
  absl::statusor
  absl::strings
  protobuf::libprotoc
)

enable_testing()
add_custom_command(
  OUTPUT ${generated_sources_dir}/distribution.pb.h ${generated_sources_dir}/distribution.pb.cc
  COMMAND ${protobuf_BINARY_DIR}/protoc -I=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=${generated_sources_dir} ${CMAKE_CURRENT_SOURCE_DIR}/distribution.proto
  DEPENDS ${protobuf_BINARY_DIR}/protoc ${CMAKE_CURRENT_SOURCE_DIR}/distribution.proto
  VERBATIM
)
add_executable(
  utils_tests 
  logging_test.cc
  adaptive_work_test.cc
  status_macros_test.cc
  regex_test.cc
  protobuf_test.cc
  distribution.pb.cc
)
target_include_directories(
  utils_tests
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${generated_sources_dir}
)
target_link_libraries(
  utils_tests
# utils targets
  logging
  adaptive_work
  status_macros
  regex
  protobuf
# third_party targets
  absl::statusor
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(utils_tests)

