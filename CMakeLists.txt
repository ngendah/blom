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

if(ANDROID_NDK)
  message(STATUS "Cross compiling requires protobuf binaries v24.3+ 
  to be already installed on the build system,
   https://github.com/protocolbuffers/protobuf/releases")
  find_program(PROTOC_COMPILER protoc REQUIRED)
  set(protobuf_BUILD_LIBPROTOC ON)
  set(
    WITH_PROTOC
    ${PROTOC_COMPILER}
    CACHE FILEPATH
    "protobuf compiler"
  )
endif()

add_subdirectory(third_party)
add_subdirectory(decision_forests)
add_subdirectory(tests)
