# testing executable
enable_testing()
add_executable(serving_decision_forest_tests)
target_link_directories(
  serving_decision_forest_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  serving_decision_forest_tests
  PRIVATE
  serving_decision_forest_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(utils_tests)
endif()

