cmake_minimum_required(VERSION 3.22)
include(FetchContent)

FetchContent_Declare(
        eigen3
        GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
        GIT_TAG "3.4.0"
        SOURCE_SUBDIR  cmake
)

FetchContent_Declare(
        com_google_test
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG "v1.14.0"
)

FetchContent_Populate(
        com_google_abseil
        URL "https://github.com/abseil/abseil-cpp/releases/download/20230802.2/abseil-cpp-20230802.2.tar.gz"
        SOURCE_DIR abseil
)

FetchContent_Populate(
        org_boost_math
        URL "https://github.com/boostorg/math/archive/refs/tags/boost-1.83.0.tar.gz"
        SOURCE_DIR boost_math
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

FetchContent_Populate(
        rapidjson
        URL "https://github.com/Tencent/rapidjson/archive/v1.1.0.zip"
        URL_HASH "SHA256=8e00c38829d6785a2dfb951bb87c6974fa07dfe488aa5b25deec4b8bc0f6a3ab"
        SOURCE_DIR rapidjson
)

FetchContent_Populate(
        protobuf
        URL "https://github.com/protocolbuffers/protobuf/releases/download/v24.3/protobuf-24.3.tar.gz"
        URL_HASH "SHA256=07d69502e58248927b58c7d7e7424135272ba5b2852a753ab6b67e62d2d29355"
        SOURCE_DIR protobuf
)

FetchContent_MakeAvailable(eigen3 com_google_test)

add_subdirectory(abseil)
add_subdirectory(boost_math)
add_subdirectory(farmhash)
add_subdirectory(zlib)
add_subdirectory(rapidjson)