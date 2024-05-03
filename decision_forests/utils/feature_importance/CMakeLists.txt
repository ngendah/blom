add_library(
  feature_importance
  STATIC
  feature_importance.cc
)
target_include_directories(
  feature_importance
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  feature_importance
  PRIVATE
  dataset_proto
  utils_concurrency
  utils_registration
  absl::status
  absl::statusor
  absl::memory
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(utils_feature_importance ALIAS feature_importance)


