generate_cpp_from_protos("*.proto" ${CMAKE_CURRENT_SOURCE_DIR})

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

add_library(
  bytestream
  STATIC
  bytestream.cc
)
target_include_directories(
  bytestream
  PRIVATE
  ${absl_SOURCE_DIR}
)
target_link_libraries(
  bytestream
  PRIVATE
  absl::status
  absl::statusor
  absl::strings
)

add_library(
  filesystem
  STATIC
  filesystem_default.cc
  filesystem.cc
)
target_include_directories(
  filesystem
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  filesystem
  PRIVATE
  absl::strings
  absl::random_distributions
  absl::random_seed_sequences
  absl::random_internal_randen
  protobuf::libprotoc
)
if(NOT ${ANDROID_PLATFORM})
  target_link_libraries(
    filesystem
    PRIVATE
    stdc++fs
  )
endif()

add_library(
  sharded_io
  STATIC
  sharded_io.cc
)
target_include_directories(
  sharded_io
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  sharded_io
  PRIVATE
  logging
  filesystem
  absl::strings
  absl::status
  absl::statusor
  absl::string_view
  protobuf::libprotoc
)

add_library(
  registration
  STATIC
  registration.cc
)
target_include_directories(
  registration
  PRIVATE
  ${absl_SOURCE_DIR}
)
target_link_libraries(
  registration
  PRIVATE
  absl::status
  absl::statusor
  absl::memory
)

# add_library(
#   csv
#   STATIC
#   csv.cc
# )
# target_include_directories(
#   csv
#   PRIVATE
#   ${absl_SOURCE_DIR}
# )
# target_link_libraries(
#   csv
#   PRIVATE
#   absl::status
#   absl::statusor
#   absl::strings
#   protobuf::libprotoc
# )


# Testing artifacts

file(GLOB_RECURSE test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  utils_tests 
  OBJECT
  ${test_SRC_FILES}
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
  PRIVATE
# utils targets
  logging
  adaptive_work
  status_macros
  regex
  protobuf
  bytestream
  filesystem
  sharded_io
  registration
# third_party targets
  absl::statusor
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

