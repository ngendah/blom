generate_cpp_from_protos("*.proto" ${CMAKE_CURRENT_SOURCE_DIR})

# add_library(
#   metric
#   STATIC
#   metric.cc
# )
# target_include_directories(
#   metric
#   PRIVATE
#   ${absl_SOURCE_DIR}
#   ${protobuf_SOURCE_DIR}/src
# )
# target_link_libraries(
#   metric
#   PRIVATE
#   absl::string_view
#   protobuf::libprotoc
# )
# 
# 
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

