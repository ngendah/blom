add_library(
  ranking_utils
  STATIC
  ranking_mrr.cc
  ranking_ndcg.cc
)
target_include_directories(
  ranking_utils
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
)
target_link_libraries(
  ranking_utils
  PRIVATE
  absl::string_view
  protobuf::libprotoc
)
add_library(metric_ranking_utils ALIAS ranking_utils)

add_library(
  report
  STATIC
  report.cc
)
target_include_directories(
  report
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  report
  PRIVATE
  model_proto
  utils_distribution
  utils_html
  utils_plot
  absl::strings
  absl::random_distributions
  absl::random_seed_sequences
  absl::random_internal_randen
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(metric_report ALIAS report)

add_library(
  comparison
  STATIC
  comparison.cc
)
target_include_directories(
  comparison
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  comparison
  PRIVATE
  metric_proto
  model_proto
  ranking_utils
  dataset_proto
  absl::strings
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(metric_comparison ALIAS comparison)

add_library(
  uplift
  STATIC
  uplift.cc
)
target_include_directories(
  uplift
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  uplift
  PRIVATE
  dataset_proto
  metric_proto
  model_proto
  metric_comparison
  absl::strings
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(metric_uplift ALIAS uplift)

add_library(
  metric
  STATIC
  metric.cc
  report.cc
)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(metric PRIVATE -Wno-return-type)
endif()
target_include_directories(
  metric
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  metric
  PRIVATE
  metric_proto
  metric_ranking_utils
  metric_uplift
  utils_concurrency
  utils_html
  utils_plot
  absl::strings
  absl::random_distributions
  absl::random_seed_sequences
  absl::random_internal_randen
  protobuf::libprotoc
)
add_library(metric_metric ALIAS metric)


# Testing artifact

file(GLOB_RECURSE test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  metric_tests_obj 
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  metric_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${farmhash_SOURCE_DIR}/src
  ${protobuf_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  metric_tests_obj
  PRIVATE
# other project objects
  utils_proto
  dataset_proto
  model_proto
  metric_metric
  metric_ranking_utils
  metric_comparison
  metric_uplift
  dataset_vertical_dataset
  utils_concurrency
  utils_distribution
  utils_filesystem
  utils_testing_utils
# third_party objects
  GTest::gtest_main GTest::gmock_main
)

