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
