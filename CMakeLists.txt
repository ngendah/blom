cmake_minimum_required(VERSION 3.22)
cmake_policy(VERSION 3.20)

project(blom)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
  add_compile_definitions(
    -DNDEBUG
    -DWIN32_LEAN_AND_MEAN
    -D_USE_MATH_DEFINES
  )
  add_compile_options(
    /Zc:preprocessor
    /Zc:__cplusplus
    /wd4244
    /wd4715
    /wd4805
  )
endif()
if(NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES ${CMAKE_SYSTEM_NAME})
  set(
    CMAKE_CROSSCOMPILING
    TRUE
    CACHE STRING
    "Indication whether cross-compilation is active"
  )
endif()
if(NOT PROJECT_BUILD_DIR)
  message(SEND_ERROR "Missing PROJECT_BUILD_DIR, set the projects build directory or pass it on command line -DPROJECT_BUILD_DIR=.. or set as a cacheVariable on presets")
  return()
endif()

add_subdirectory(third_party)
if(NOT CMAKE_CROSSCOMPILING)
  export(
    TARGETS protoc
    NAMESPACE "${PROJECT_NAME}::"
    FILE "${PROJECT_BUILD_DIR}/ProtoBufConfig.cmake"
  )
  set(
    PROTOC_COMPILER
    protoc
    CACHE
    FILEPATH
    ""
  )
endif()
if(CMAKE_CROSSCOMPILING)
  include(${PROJECT_BUILD_DIR}/ProtoBufConfig.cmake)
  set(
    PROTOC_COMPILER
    "${PROJECT_NAME}::protoc"
    CACHE
    FILEPATH
    ""
  )
endif()
add_subdirectory(decision_forests)
add_subdirectory(tests)
add_subdirectory(example)

