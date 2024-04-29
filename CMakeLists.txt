cmake_minimum_required(VERSION 3.22)
cmake_policy(VERSION 3.20)

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

# Eigen3 configuration
set(BUILD_TESTING OFF)

add_subdirectory(third_party)
add_subdirectory(decision_forests)
add_subdirectory(tests)
