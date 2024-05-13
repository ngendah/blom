set(ABSL_FIND_GOOGLETEST OFF)
set(ABSL_USE_EXTERNAL_GOOGLETEST ON)
set(ABSL_PROPAGATE_CXX_STD ON)
# https://github.com/protocolbuffers/protobuf/issues/12185
set(ABSL_ENABLE_INSTALL ON)

FetchContent_Declare(
 abseil
 URL "https://github.com/abseil/abseil-cpp/releases/download/20230802.2/abseil-cpp-20230802.2.tar.gz"
 URL_HASH "SHA256=7c11539617af1f332f0854a6fb21e296a1b29c27d03f23c7b49d4adefcd102cc"
)
FetchContent_MakeAvailable(abseil)


