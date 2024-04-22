add_library(
  distribution_proto
  OBJECT
  distribution.proto
)
target_include_directories(
  distribution_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
protobuf_generate(
  TARGET distribution_proto
  IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
)

