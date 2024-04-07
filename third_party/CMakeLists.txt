include(FetchContent)

FetchContent_Declare(
        eigen3
        GIT_REPOSITORY "https://gitlab.com/libeigen/eigen.git"
        GIT_TAG "3.4.0"
        SOURCE_SUBDIR  cmake
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

FetchContent_MakeAvailable(eigen3)

add_subdirectory(abseil)  # git submodule
add_subdirectory(boost_math) # git submodule
add_subdirectory(googletest) # git submodule

add_subdirectory(zlib)
add_subdirectory(rapidjson)

file(GLOB_RECURSE farmhash RELATIVE farmhash/src *.cpp *.h)