cmake_path(SET PROTOC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(SET PROTOC_GENERATED_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_library(
  utils_proto
  STATIC
  utils/distribution.proto
)
target_include_directories(
  utils_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET utils_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
)

add_library(
  dataset_proto
  STATIC
  dataset/data_spec.proto
  dataset/example.proto
  dataset/formats.proto
  dataset/weight.proto
)
target_include_directories(
  dataset_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET dataset_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
)

add_library(
  model_proto
  STATIC
  model/prediction.proto
  model/abstract_model.proto
  model/hyperparameter.proto
)
target_include_directories(
  model_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET model_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
)

add_library(
  metric_proto
  STATIC
  metric/metric.proto
)
target_include_directories(
  metric_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  metric_proto
  PRIVATE
  model_proto
)
protobuf_generate(
  TARGET metric_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
)

