# testing executable
enable_testing()
add_executable(learner_optimizers_random_tests)
target_link_directories(
  learner_optimizers_random_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  learner_optimizers_random_tests
  PRIVATE
  learner_optimizers_random_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(learner_optimizers_random_tests)
endif()

