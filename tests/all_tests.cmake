# testing executable
enable_testing()
add_executable(yggdrasil_tests)
target_link_directories(
  yggdrasil_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  yggdrasil_tests
  PRIVATE
  utils_tests_obj
  utils_distribute_tests_obj
  dataset_tests_obj
  metric_tests_obj
)
include(GoogleTest)
gtest_discover_tests(yggdrasil_tests)

