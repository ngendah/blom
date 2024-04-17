generate_cpp_from_protos("*.proto" ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
  formats
  STATIC
  formats.cc
  formats.pb.cc
)
target_include_directories(
  formats
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  formats
  PRIVATE
  logging
  absl::string_view
  protobuf::libprotoc
)

enable_testing()
file(GLOB test_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*test.cc)
add_executable(
  dataset_tests 
  ${test_SRC_FILES}
)
target_include_directories(
  dataset_tests
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  dataset_tests
# local targets
  formats
# third_party targets
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(dataset_tests)

