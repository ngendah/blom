set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)

include(FetchContent)
include(abseil.cmake)
include(googletest.cmake)
include(farmhash.cmake)
include(boost_math.cmake)
include(protobuf.cmake)
include(eigen3.cmake)

# https://github.com/protocolbuffers/protobuf/issues/12185

# FetchContent_Declare(
#  rapidjson
#  URL "https://github.com/Tencent/rapidjson/archive/v1.1.0.zip"
#  URL_HASH "SHA256=8e00c38829d6785a2dfb951bb87c6974fa07dfe488aa5b25deec4b8bc0f6a3ab"
# )
# 
# FetchContent_Declare(
#  grpc
#  URL "https://github.com/grpc/grpc/archive/refs/tags/v1.58.1.tar.gz"
#  URL_HASH "SHA256=860bf758a1437a03318bf09db8e87cb8149a2f578954110ce8549e147f868b62"
# )
# 
# FetchContent_Populate(
#  zlib
#  URL "https://github.com/madler/zlib/archive/refs/tags/v1.2.11.tar.gz"
#  SOURCE_DIR zlib
# )

