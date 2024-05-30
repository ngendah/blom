cmake_minimum_required(VERSION 3.22)
cmake_policy(VERSION 3.20)

project(blom LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(blom_BUILD_TESTS "Build tests" ON)

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
  set(blom_BUILD_TESTS OFF)
  include(${PROJECT_BUILD_DIR}/ProtoBufConfig.cmake)
  set(
    PROTOC_COMPILER
    "${PROJECT_NAME}::protoc"
    CACHE
    FILEPATH
    ""
  )
endif()
if(blom_BUILD_TESTS)
  enable_testing()
  add_custom_target(
    test_data ALL
    DEPENDS testing_data
  )
  add_custom_command(
    OUTPUT testing_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${PROJECT_SOURCE_DIR}/testing_data
      ${PROJECT_BINARY_DIR}/testing_data
  )
  set_property(
    TARGET test_data
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${PROJECT_BINARY_DIR}/testing_data
  )
endif()
add_subdirectory(decision_forests)
add_subdirectory(example)

