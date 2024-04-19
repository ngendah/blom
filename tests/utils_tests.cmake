# testing executable
enable_testing()
add_executable(util_test)
target_link_directories(
  util_test
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  util_test
  PRIVATE
  utils_tests
)
include(GoogleTest)
gtest_discover_tests(util_test)

