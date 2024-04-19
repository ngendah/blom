# testing executable
enable_testing()
add_executable(dataset_test)
target_link_directories(
  dataset_test
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  dataset_test
  PRIVATE
  dataset_tests
  utils_tests
)
include(GoogleTest)
gtest_discover_tests(dataset_test)

