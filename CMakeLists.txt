cmake_minimum_required(VERSION 3.22)
cmake_policy(VERSION 3.20)

project(yggdrasil)

set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)
if(NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES ${CMAKE_SYSTEM_NAME})
  set(
    CMAKE_CROSSCOMPILING
    TRUE
    CACHE STRING
    "Indication whether cross-compilation is active"
  )
endif()

# googletest
set(INSTALL_GTEST OFF)

# abseil configurations
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(ABSL_FIND_GOOGLETEST OFF)
set(ABSL_USE_EXTERNAL_GOOGLETEST ON)
set(ABSL_PROPAGATE_CXX_STD ON)
set(ABSL_ENABLE_INSTALL ON)

# protocal buffer configurations
set(protobuf_ABSL_PROVIDER package)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_LIBUPB OFF)
set(protobuf_BUILD_LIBPROTOC ON)
set(protobuf_BUILD_PROTOBUF_BINARIES ON)
if(NOT CMAKE_CROSSCOMPILING)
  set(protobuf_BUILD_PROTOC_BINARIES ON)
endif()
if(CMAKE_CROSSCOMPILING)
  set(protobuf_BUILD_PROTOC_BINARIES OFF)
endif()

add_subdirectory(third_party)

if(NOT CMAKE_CROSSCOMPILING)
  export(
    TARGETS
    protoc
    NAMESPACE "${PROJECT_NAME}::"
    FILE
    "${PROJECT_BUILD_DIR}/ProtoBufConfig.cmake"
  )
  set(PROTOC_COMPILER protobuf::protoc)
endif()
if(CMAKE_CROSSCOMPILING)
  include(${PROJECT_BUILD_DIR}/ProtoBufConfig.cmake)
  set(PROTOC_COMPILER ${PROJECT_NAME}::protoc)
endif()

add_subdirectory(decision_forests)
add_subdirectory(tests)
