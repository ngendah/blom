# testing executable
enable_testing()
add_executable(metric_tests)
target_link_directories(
  metric_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  metric_tests
  PRIVATE
  metric_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(metric_tests)
endif()

