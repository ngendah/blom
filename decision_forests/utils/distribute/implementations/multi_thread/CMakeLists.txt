add_library(
  multi_thread
  STATIC
  multi_thread.cc
)
target_include_directories(
  multi_thread
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  multi_thread
  PRIVATE
  utils_proto
  logging
  concurrency
  protobuf::libprotoc
)
add_library(utils_multi_thread ALIAS multi_thread)

