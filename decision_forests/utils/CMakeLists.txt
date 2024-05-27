add_subdirectory(distribute)
add_subdirectory(feature_importance)

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
add_library(utils_logging ALIAS logging)

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
add_library(utils_adaptive_work ALIAS adaptive_work)

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
add_library(utils_regex ALIAS regex)

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
  utils_logging
  absl::status
  absl::statusor
  absl::strings
  protobuf::libprotoc
)
add_library(utils_protobuf ALIAS protobuf)

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
add_library(utils_bytestream ALIAS bytestream)

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
  utils_bytestream
  absl::strings
  absl::random_distributions
  absl::random_seed_sequences
  absl::random_internal_randen
  protobuf::libprotoc
)
if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS_EQUAL 9.0)
  target_link_libraries(
    filesystem
    PRIVATE
    stdc++fs
  )
endif()
add_library(utils_filesystem ALIAS filesystem)

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
  utils_proto
  utils_logging
  utils_filesystem
  absl::strings
  absl::status
  absl::statusor
  absl::string_view
  protobuf::libprotoc
)
add_library(utils_sharded_io ALIAS sharded_io)

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
add_library(utils_registration ALIAS registration)

add_library(
  concurrency
  STATIC
  concurrency.cc
  concurrency_default.cc
)
target_include_directories(
  concurrency
  PRIVATE
  ${absl_SOURCE_DIR}
)
target_link_libraries(
  concurrency
  PRIVATE
  utils_logging
)
add_library(utils_concurrency ALIAS concurrency)

add_library(
  html
  STATIC
  html.cc
)
target_include_directories(
  html
  PRIVATE
  ${absl_SOURCE_DIR}
)
target_link_libraries(
  html
  PRIVATE
  absl::strings
)
add_library(utils_html ALIAS html)

add_library(
  distribution
  STATIC
  distribution.cc
)
target_include_directories(
  distribution
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  distribution
  PRIVATE
  utils_proto
  utils_logging
  utils_html
  absl::strings
  absl::cord
  absl::string_view
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(utils_distribution ALIAS distribution)

add_library(
  plot
  STATIC
  plot.cc
)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(plot PRIVATE -Wno-return-type)
endif()
target_include_directories(
  plot
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
)
target_link_libraries(
  plot
  PRIVATE
  utils_logging
  utils_html
  absl::strings
  absl::cord
  absl::string_view
  absl::random_distributions
  absl::random_seed_sequences
  absl::random_internal_randen
  farmhash::farmhash
)
add_library(utils_plot ALIAS plot)

add_library(
  csv
  STATIC
  csv.cc
)
target_include_directories(csv PRIVATE ${absl_SOURCE_DIR})
target_link_libraries(
  csv
  PRIVATE
utils_filesystem
  absl::strings
)
add_library(utils_csv ALIAS csv)

add_library(
  hyper_parameters
  STATIC
  hyper_parameters.cc
)
target_include_directories(
  hyper_parameters
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  hyper_parameters
  PRIVATE
  learner_proto
  absl::strings
  absl::status
  absl::statusor
  protobuf::libprotoc
)
add_library(utils_hyper_parameters ALIAS hyper_parameters)

add_library(
  fold_generator
  STATIC
  fold_generator.cc
)
target_include_directories(
  fold_generator
  PRIVATE
  ${absl_SOURCE_DIR}
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  fold_generator
  PRIVATE
  dataset_proto
  dataset_data_spec 
  dataset_vertical_dataset
  utils_csv
  utils_filesystem
  utils_logging
  absl::strings
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(utils_fold_generator ALIAS fold_generator)

add_library(
  bitmap
  STATIC
  bitmap.cc
)
target_include_directories(
  bitmap
  PRIVATE
  ${absl_SOURCE_DIR}
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  bitmap
  PRIVATE
  utils_proto
  utils_concurrency
  utils_filesystem
  absl::strings
  protobuf::libprotoc
)
add_library(utils_bitmap ALIAS bitmap)

add_library(
  blob_sequence
  STATIC
  blob_sequence.cc
)
target_include_directories(
  blob_sequence
  PRIVATE
  ${absl_SOURCE_DIR}
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  blob_sequence
  PRIVATE
  utils_bytestream
  absl::strings
  absl::status
  absl::statusor
)
add_library(utils_blob_sequence ALIAS blob_sequence)

add_library(
  usage
  STATIC
  usage_default.cc
)
target_include_directories(
  usage
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  usage
  PRIVATE
  model_proto
  dataset_proto
  learner_proto
  absl::strings
  absl::status
  absl::statusor
  absl::time
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(utils_usage ALIAS usage)

add_library(
  evaluation
  STATIC
  evaluation.cc
)
target_include_directories(
  evaluation
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  evaluation
  PRIVATE
  dataset_proto
  utils_proto
  dataset_example_writer
  dataset_formats
  utils_distribution
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(utils_evaluation ALIAS evaluation)

add_library(
  test_util
  STATIC
  test.cc
)
target_include_directories(
  test_util
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  test_util
  PRIVATE
  utils_filesystem
  utils_logging
  absl::strings
  protobuf::libprotoc
  GTest::gmock_main
)
add_library(utils_testing_utils ALIAS test_util)

# Tests
if(blom_BUILD_TESTS)
  file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.cc)
  add_executable(
    utils_tests
    ${test_SRC_FILES}
  )
  target_include_directories(
    utils_tests
    PRIVATE
    ${absl_SOURCE_DIR}
    ${googletest_SOURCE_DIR}
    ${protobuf_SOURCE_DIR}/src
    ${farmhash_SOURCE_DIR}/src
    ${PROTOC_GENERATED_SOURCE_DIR}
  )
  target_link_libraries(
    utils_tests
    PRIVATE
    utils_proto
    dataset_proto
    learner_proto
    dataset_data_spec_inference
    dataset_formats_registration
    utils_logging
    utils_adaptive_work
    utils_regex
    utils_protobuf
    utils_bytestream
    utils_filesystem
    utils_sharded_io
    utils_registration
    utils_concurrency
    utils_html
    utils_distribution
    utils_plot
    utils_fold_generator
    utils_hyper_parameters
    utils_bitmap
    utils_blob_sequence
    utils_evaluation
    utils_testing_utils
    absl::statusor
    protobuf::libprotoc
    GTest::gtest_main GTest::gmock_main
  )
  blom_test_target(utils_tests)
  gtest_discover_tests(utils_tests)
endif()

