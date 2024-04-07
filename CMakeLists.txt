cmake_minimum_required(VERSION 3.22)

SET (CMAKE_C_COMPILER "clang" CACHE STRING "C compiler" FORCE)
SET (CMAKE_CXX_COMPILER "clang" CACHE STRING "C++ compiler" FORCE)

project(yggdrasil)
set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(third_party)
add_subdirectory(decision_forests)
