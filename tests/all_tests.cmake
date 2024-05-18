# testing executable
enable_testing()
add_executable(blom_tests)
target_link_directories(
  blom_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  blom_tests
  PRIVATE
  metric_tests_obj
  serving_tests_obj
  model_tests_obj
  model_decision_tree_tests_obj
  model_random_forest_tests_obj
  serving_decision_forest_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(blom_tests)
endif()

