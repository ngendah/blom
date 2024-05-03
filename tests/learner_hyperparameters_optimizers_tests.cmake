# testing executable
enable_testing()
add_executable(learner_hyperparameters_optimizer_tests)
target_link_directories(
  learner_hyperparameters_optimizer_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  learner_hyperparameters_optimizer_tests
  PRIVATE
  learner_hyperparameters_optimizer_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(learner_hyperparameters_optimizer_tests)
endif()

