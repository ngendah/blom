add_library(
  data_spec_proto
  OBJECT
  data_spec.proto
)
target_include_directories(
  data_spec_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
protobuf_generate(
  TARGET data_spec_proto
  IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(
  example_proto
  OBJECT
  example.proto
)
target_include_directories(
  example_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
protobuf_generate(
  TARGET example_proto
  IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(
  formats_proto
  OBJECT
  formats.proto
)
target_include_directories(
  formats_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
protobuf_generate(
  TARGET formats_proto
  IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(
  weight_proto
  OBJECT
  weight.proto
)
target_include_directories(
  weight_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
protobuf_generate(
  TARGET weight_proto
  IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  PROTOC_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
)

