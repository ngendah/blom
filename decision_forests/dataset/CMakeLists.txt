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

add_library(
  data_spec
  STATIC
  data_spec.cc
  example.pb.cc
  data_spec.pb.cc
)
target_include_directories(
  data_spec
  PRIVATE
  ${absl_SOURCE_DIR}
  ${farmhash_SOURCE_DIR}/src
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  data_spec
  PRIVATE
  logging
  regex
  absl::strings
  absl::string_view
  farmhash::farmhash
  protobuf::libprotoc
)

add_library(
  example_builder
  STATIC
  example_builder.cc
  example.pb.cc
  data_spec.pb.cc
)
target_include_directories(
  example_builder
  PRIVATE
  ${absl_SOURCE_DIR}
  ${farmhash_SOURCE_DIR}/src
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  example_builder
  PRIVATE
  logging
  data_spec
  absl::string_view
  protobuf::libprotoc
)
# 
# add_library(
#   vertical_dataset
#   STATIC
#   vertical_dataset.cc
#   example.pb.cc
#   data_spec.pb.cc
# )
# target_include_directories(
#   vertical_dataset
#   PRIVATE
#   ${absl_SOURCE_DIR}
#   ${farmhash_SOURCE_DIR}/src
#   ${protobuf_SOURCE_DIR}/src
# )
# target_link_libraries(
#   vertical_dataset
#   PRIVATE
#   status_macros
#   logging
#   data_spec
#   example_builder
#   absl::string_view
#   absl::cord
#   absl::statusor
#   absl::memory
#   farmhash::farmhash
#   protobuf::libprotoc
# )

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
  ${farmhash_SOURCE_DIR}/src
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  dataset_tests
# local targets
  formats
  data_spec
  example_builder
# third_party targets
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(dataset_tests)

