cmake_minimum_required(VERSION 3.22)

project(yggdrasil)

# TODO mv to CMakeUserPresets.json
set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)
set(CMAKE_BUILD_TYPE Debug)
set(INSTALL_GTEST OFF)

# abseil configurations
set(ABSL_FIND_GOOGLETEST OFF)
set(ABSL_USE_EXTERNAL_GOOGLETEST ON)
set(ABSL_PROPAGATE_CXX_STD ON)

# protocal buffer configurations
set(protobuf_ABSL_PROVIDER package)
set(protobuf_USE_EXTERNAL_GTEST ON)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_LIBUPB OFF)
set(protobuf_BUILD_PROTOBUF_BINARIES ON)

add_subdirectory(third_party)
add_subdirectory(decision_forests)

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
  utils_tests
)
include(GoogleTest)
gtest_discover_tests(yggdrasil_tests)

