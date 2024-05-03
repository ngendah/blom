# testing executable
enable_testing()
add_executable(learner_random_forest_tests)
target_link_directories(
  learner_random_forest_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  learner_random_forest_tests
  PRIVATE
  learner_random_forest_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(learner_random_forest_tests)
endif()

