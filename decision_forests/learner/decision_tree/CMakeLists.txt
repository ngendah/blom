add_library(
  utils
  STATIC
  utils.cc
)
target_include_directories(
  utils
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  utils
  PRIVATE
  model_proto
  utils_bitmap
  utils_concurrency
  utils_logging
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(learner_decision_tree_utils ALIAS utils)

add_library(
  generic_parameters
  STATIC
  generic_parameters.cc
)
target_include_directories(
  generic_parameters
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  generic_parameters
  PRIVATE
  learner_proto
  utils_hyper_parameters
  utils_logging
  utils_status_macros
  absl::status
  absl::statusor
  absl::strings
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(learner_decision_tree_generic_parameters ALIAS generic_parameters)

add_library(
  oblique
  STATIC
  oblique.cc
)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(oblique PRIVATE -Wno-return-type -Wno-non-template-friend -Wno-attributes)
endif()
target_include_directories(
  oblique
  PRIVATE
  ${absl_SOURCE_DIR}
  ${Eigen3_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  oblique
  PRIVATE
  dataset_proto
  learner_proto
  dataset_vertical_dataset
  learner_decision_tree_utils
  utils_logging
  absl::status
  absl::statusor
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(learner_decision_tree_oblique ALIAS oblique)

add_library(
  training
  STATIC
  training.cc
)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(training PRIVATE -Wno-return-type -Wno-non-template-friend -Wno-attributes)
endif()
target_include_directories(
  training
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  training
  PRIVATE
  dataset_proto
  learner_proto
  model_proto
  utils_proto
  dataset_data_spec
  dataset_vertical_dataset
  dataset_types
  learner_decision_tree_oblique
  model_decision_tree
  utils_concurrency
  utils_distribution
  utils_logging
  utils_status_macros
  absl::strings
  absl::statusor
  absl::strings
  absl::time
  protobuf::libprotoc
  farmhash::farmhash
)
add_library(learner_decision_tree_training ALIAS training)


# Testing artifact

file(GLOB test_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *test.cc)
add_library(
  learner_decision_tree_tests_obj
  OBJECT
  ${test_SRC_FILES}
)
if(CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(learner_decision_tree_tests_obj PRIVATE -Wno-return-type -Wno-non-template-friend -Wno-attributes)
endif()
target_include_directories(
  learner_decision_tree_tests_obj
  PRIVATE
  ${absl_SOURCE_DIR}
  ${googletest_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${farmhash_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_decision_tree_tests_obj
  PRIVATE
  dataset_proto
  model_proto
  learner_decision_tree_training
  learner_decision_tree_oblique
  learner_decision_tree_utils
  learner_decision_tree_generic_parameters
  utils_testing_utils
  # third_party objects
  absl::status
  absl::statusor
  absl::strings
  protobuf::libprotoc
  GTest::gtest_main GTest::gmock_main
)

