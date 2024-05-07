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

# silence -Wattributes warning
add_compile_options(-Wno-attributes)

FetchContent_Declare(
 protobuf
 URL "https://github.com/protocolbuffers/protobuf/releases/download/v24.3/protobuf-24.3.tar.gz"
 URL_HASH "SHA256=07d69502e58248927b58c7d7e7424135272ba5b2852a753ab6b67e62d2d29355"
)
FetchContent_MakeAvailable(protobuf)
include(protobuf_generate.cmake)

# enable -Wattributes warning
add_compile_options(-Wattributes)

