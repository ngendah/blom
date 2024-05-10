add_executable(example example.cc)
target_include_directories(
  example
  PRIVATE
  ${absl_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/decision_forests
  ${PROJECT_BINARY_DIR}/decision_forests
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
)
target_link_directories(
  example
  PUBLIC
  ${PROJECT_BINARY_PATH}/decision_forests
)
target_link_libraries(
  example
  PRIVATE
  dataset_proto
  dataset_formats_registration
  learner_learners_registration
  metric_metric
  metric_report
  model_library
  model_models_registration
  serving_fast_engine_registration
  utils_filesystem
  utils_logging
)
add_custom_command(
  TARGET example POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/testing_data
  ${CMAKE_CURRENT_BINARY_DIR}/testing_data
)

