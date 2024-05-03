# testing executable
enable_testing()
add_executable(learner_generic_worker_tests)
target_link_directories(
  learner_generic_worker_tests
  PUBLIC
  ${CMAKE_PROJECT_PATH}/decision_forests
)
target_link_libraries(
  learner_generic_worker_tests
  PRIVATE
  learner_generic_worker_tests_obj
)
if(NOT CMAKE_CROSSCOMPILING)
  include(GoogleTest)
  gtest_discover_tests(learner_generic_worker_tests)
endif()
