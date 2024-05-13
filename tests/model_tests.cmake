# testing executable
enable_testing()
add_executable(model_tests)
target_link_directories(
  model_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  model_tests
  PRIVATE
  model_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(model_tests)
endif()

