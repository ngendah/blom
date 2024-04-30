# testing executable
enable_testing()
add_executable(learner_tests)
target_link_directories(
  learner_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  learner_tests
  PRIVATE
  learner_tests_obj
)
if(NOT ANDROID_NDK)
  include(GoogleTest)
  gtest_discover_tests(utils_tests)
endif()

