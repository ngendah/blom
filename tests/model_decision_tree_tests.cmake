# testing executable
enable_testing()
add_executable(model_decision_tree_tests)
target_link_directories(
  model_decision_tree_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  model_decision_tree_tests
  PRIVATE
  model_decision_tree_tests_obj
)
include(GoogleTest)
gtest_discover_tests(model_decision_tree_tests)
