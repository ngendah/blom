# testing executable
enable_testing()
add_executable(dataset_tests)
target_link_directories(
  dataset_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  dataset_tests
  PRIVATE
  dataset_tests_obj
)
include(GoogleTest)
gtest_discover_tests(dataset_tests)

