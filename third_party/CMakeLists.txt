include(FetchContent)

FetchContent_Declare(
 googletest
 URL "https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz"
 URL_HASH "SHA256=8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7"
)

FetchContent_MakeAvailable(googletest)

# https://github.com/protocolbuffers/protobuf/issues/12185

set(ABSL_ENABLE_INSTALL ON)

FetchContent_Declare(
 abseil
 URL "https://github.com/abseil/abseil-cpp/releases/download/20230802.2/abseil-cpp-20230802.2.tar.gz"
)

FetchContent_MakeAvailable(abseil)

FetchContent_Declare(
 protobuf
 URL "https://github.com/protocolbuffers/protobuf/releases/download/v24.3/protobuf-24.3.tar.gz"
 URL_HASH "SHA256=07d69502e58248927b58c7d7e7424135272ba5b2852a753ab6b67e62d2d29355"
)

FetchContent_MakeAvailable(protobuf)

FetchContent_Declare(
 rapidjson
 URL "https://github.com/Tencent/rapidjson/archive/v1.1.0.zip"
 URL_HASH "SHA256=8e00c38829d6785a2dfb951bb87c6974fa07dfe488aa5b25deec4b8bc0f6a3ab"
)

FetchContent_Declare(
 eigen3
 URL "https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"
)

FetchContent_Declare(
 grpc
 URL "https://github.com/grpc/grpc/archive/refs/tags/v1.58.1.tar.gz"
 URL_HASH "SHA256=860bf758a1437a03318bf09db8e87cb8149a2f578954110ce8549e147f868b62"
)

FetchContent_Populate(
 farmhash
 URL "https://github.com/google/farmhash/archive/master.zip"
 URL_HASH "SHA256=d27a245e59f5e10fba10b88cb72c5f0e03d3f2936abbaf0cb78eeec686523ec1"
 SOURCE_DIR farmhash
)

FetchContent_Populate(
 zlib
 URL "https://github.com/madler/zlib/archive/refs/tags/v1.2.11.tar.gz"
 SOURCE_DIR zlib
)

include(farmhash.cmake)
