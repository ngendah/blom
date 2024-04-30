# testing executable
enable_testing()
add_executable(utils_distribute_tests)
target_link_directories(
  utils_distribute_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  utils_distribute_tests
  PRIVATE
  utils_distribute_tests_obj
)
if(NOT ANDROID_NDK)
  include(GoogleTest)
  gtest_discover_tests(utils_tests)
endif()

