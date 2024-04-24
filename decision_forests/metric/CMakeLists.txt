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

add_library(
  metric
  STATIC
  metric.cc
)
target_include_directories(
  metric
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  metric
  PRIVATE
  metric_proto
  absl::strings
  protobuf::libprotoc
)


# # Testing artifact
# 
# file(GLOB_RECURSE test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
# add_library(
#   metric_tests_obj 
#   OBJECT
#   ${test_SRC_FILES}
# )
# target_include_directories(
#   metric_tests_obj
#   PRIVATE
#   ${absl_SOURCE_DIR}
#   ${googletest_SOURCE_DIR}
#   ${farmhash_SOURCE_DIR}/src
#   ${protobuf_SOURCE_DIR}/src
# )
# target_link_libraries(
#   metric_tests_obj
#   PRIVATE
# # local objects
# # third_party objects
#   GTest::gtest_main GTest::gmock_main
# )

