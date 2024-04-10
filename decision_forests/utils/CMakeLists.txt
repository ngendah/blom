add_library(
 utils
 OBJECT
 adaptive_work.cc
 logging_default.cc
)

target_include_directories(utils PUBLIC ${absl_SOURCE_DIR})

enable_testing()
add_executable(
  utils_tests 
  adaptive_work_test.cc
)
target_include_directories(utils_tests PRIVATE ${absl_SOURCE_DIR})
target_link_libraries(
  utils_tests
  utils
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(utils_tests)
