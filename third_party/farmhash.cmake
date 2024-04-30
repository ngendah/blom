FetchContent_Populate(
 farmhash
 URL "https://github.com/google/farmhash/archive/master.zip"
 URL_HASH "SHA256=d27a245e59f5e10fba10b88cb72c5f0e03d3f2936abbaf0cb78eeec686523ec1"
 SOURCE_DIR farmhash
)

add_library(
  farmhash
  STATIC
  ${farmhash_SOURCE_DIR}/src/farmhash.cc
)
add_library(farmhash::farmhash ALIAS farmhash)
set(
  farmhash_SOURCE_DIR
  ${farmhash_SOURCE_DIR}
  CACHE PATH
  "Farmhash sources directory"
)
set(
  farmhash_BINARY_DIR
  ${farmhash_BINARY_DIR}
  CACHE PATH
  "Farmhash binary directory"
)
