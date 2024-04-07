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

FetchContent_Populate(
        grpc
        URL "https://github.com/grpc/grpc/archive/refs/tags/v1.58.1.tar.gz"
        URL_HASH "SHA256=860bf758a1437a03318bf09db8e87cb8149a2f578954110ce8549e147f868b62"
        SOURCE_DIR grpc
)

FetchContent_Populate(
        tensorflow
        URL "https://github.com/tensorflow/tensorflow/archive/refs/tags/v2.13.0.zip"
        URL_HASH "SHA256=447cdb65c80c86d6c6cf1388684f157612392723eaea832e6392d219098b49de"
        SOURCE_DIR tensorflow
)

FetchContent_MakeAvailable(eigen3)

add_subdirectory(abseil)  # git submodule
add_subdirectory(boost_math) # git submodule
add_subdirectory(googletest) # git submodule
add_subdirectory(zlib)
add_subdirectory(rapidjson)
add_subdirectory(grpc)

file(GLOB_RECURSE farmhash RELATIVE farmhash/src *.cpp *.h)