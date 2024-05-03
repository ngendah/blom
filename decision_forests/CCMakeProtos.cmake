cmake_path(SET PROTOC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(SET PROTOC_GENERATED_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_library(
  utils_proto
  STATIC
  utils/distribution.proto
  utils/fold_generator.proto
  utils/bitmap.proto
  utils/distribute/distribute.proto
  utils/distribute/implementations/multi_thread/multi_thread.proto
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
  PROTOC_COMPILER ${PROTOC_COMPILER}
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
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  model_proto
  STATIC
  model/abstract_model.proto
  model/hyperparameter.proto
  model/prediction.proto
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
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  model_decision_tree_proto
  STATIC
  model/decision_tree/decision_tree.proto
)
target_link_libraries(
  model_decision_tree_proto
  PRIVATE
  utils_proto
)
target_include_directories(
  model_decision_tree_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET model_decision_tree_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  metric_proto
  STATIC
  metric/metric.proto
)
target_link_libraries(
  metric_proto
  PRIVATE
  dataset_proto
  model_proto
  utils_proto
)
target_include_directories(
  metric_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET metric_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  model_random_forest_proto
  STATIC
  model/random_forest/random_forest.proto
)
target_link_libraries(
  model_random_forest_proto
  PRIVATE
  metric_proto
)
target_include_directories(
  model_random_forest_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET model_random_forest_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  hyperparameters_optimizer_proto
  STATIC
  learner/hyperparameters_optimizer/hyperparameters_optimizer.proto
  learner/hyperparameters_optimizer/optimizers/random.proto
)
target_include_directories(
  hyperparameters_optimizer_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  hyperparameters_optimizer_proto
  PRIVATE
  learner_proto
  metric_proto
  model_proto
)
protobuf_generate(
  TARGET hyperparameters_optimizer_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  serving_proto
  STATIC
  serving/serving.proto
)
target_include_directories(
  serving_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
protobuf_generate(
  TARGET serving_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  learner_proto
  STATIC
  learner/abstract_learner.proto
  learner/decision_tree/decision_tree.proto
  learner/cart/cart.proto
  learner/random_forest/random_forest.proto
)
target_include_directories(
  learner_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_proto
  PRIVATE
  utils_proto
  dataset_proto
  model_proto
)
protobuf_generate(
  TARGET learner_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

add_library(
  learner_generic_worker_proto
  STATIC
  learner/generic_worker/generic_worker.proto
)
target_include_directories(
  learner_generic_worker_proto
  PRIVATE
  ${absl_SOURCE_DIR}
  ${protobuf_SOURCE_DIR}/src
  ${PROTOC_GENERATED_SOURCE_DIR}
)
target_link_libraries(
  learner_generic_worker_proto
  PRIVATE
  dataset_proto
  learner_proto
  metric_proto
  model_proto
)
protobuf_generate(
  TARGET learner_generic_worker_proto
  PROTOC_OUT_DIR ${PROTOC_GENERATED_SOURCE_DIR}
  PROTOC_OPTIONS "--proto_path=${PROTOC_SOURCE_DIR}"
  PROTOC_COMPILER ${PROTOC_COMPILER}
)

