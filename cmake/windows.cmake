add_compile_definitions(
  -DNDEBUG
  -DWIN32_LEAN_AND_MEAN
  -D_USE_MATH_DEFINES
)
add_compile_options(
  /Zc:preprocessor
  /Zc:__cplusplus
  /wd4244
  /wd4715
  /wd4805
)
include(linux.cmake)

