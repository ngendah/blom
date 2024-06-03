cmake_minimum_required(VERSION 3.22)
cmake_policy(VERSION 3.20)

project(blom LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

option(blom_BUILD_TESTS "Build tests" ON)
option(blom_BUILD_EXAMPLE "Build example" ON)
set(
  PROJECT_GENERATED_CMAKE_DIR ${PROJECT_SOURCE_DIR}/_gen
  CACHE PATH
  "Project builds directory"
)

include(cmake/common.cmake)
if(LINUX)
  include(cmake/linux.cmake)
endif ()
if(WINDOWS)
  include(cmake/windows.cmake)
endif ()
if(ANDROID)
  include(cmake/android.cmake)
endif ()

