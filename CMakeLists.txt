cmake_minimum_required(VERSION 3.22)

project(yggdrasil)

set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)
set(CMAKE_BUILD_TYPE Debug)
set(ABSL_FIND_GOOGLETEST OFF)
set(ABSL_USE_EXTERNAL_GOOGLETEST ON)
set(ABSL_PROPAGATE_CXX_STD ON)
set(INSTALL_GTEST OFF)

add_subdirectory(third_party)
add_subdirectory(decision_forests)

