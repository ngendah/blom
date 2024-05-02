add_library(
  cart
  STATIC
  cart.cc
)
target_include_directories(
  cart
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  cart
  PRIVATE
  learner_proto
  metric_proto
  model_proto
  dataset_proto
  learner_abstract_learner
  learner_decision_tree_generic_parameters
  learner_decision_tree_training
  learner_decision_tree_utils
  metric_ranking_utils
  metric_metric
  model_decision_tree_random_forest
  model_decision_tree
  utils_adaptive_work
  utils_hyper_parameters
  utils_logging
  utils_status_macros
  utils_usage
  absl::string_view
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(learner_cart ALIAS cart)


# Testing artifact

file(GLOB_RECURSE test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  learner_cart_tests_obj 
  OBJECT
  ${test_SRC_FILES}
)
target_include_directories(
  learner_cart_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${farmhash_SOURCE_DIR}/src
  ${protobuf_SOURCE_DIR}/src
  ${boost_math_SOURCE_DIR}/include
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_cart_tests_obj
  PRIVATE
  model_proto
  learner_cart
  utils_filesystem
  utils_logging
  utils_testing_utils
  e2e_testing_utils
# third_party objects
  protobuf::libprotoc
  GTest::gtest
  GTest::gmock
)

