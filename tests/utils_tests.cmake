# testing executable
enable_testing()
add_executable(utils_tests)
target_link_directories(
  utils_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  utils_tests
  PRIVATE
  utils_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(utils_tests)
endif()

