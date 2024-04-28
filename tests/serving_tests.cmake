# testing executable
enable_testing()
add_executable(serving_tests)
target_link_directories(
  serving_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  serving_tests
  PRIVATE
  serving_tests_obj
)
include(GoogleTest)
gtest_discover_tests(serving_tests)
