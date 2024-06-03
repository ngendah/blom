include(FetchContent)

set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(BUILD_SHARED_LIBS OFF)

include(abseil.cmake)
include(googletest.cmake)
include(farmhash.cmake)
include(boost_math.cmake)
include(protobuf.cmake)
include(eigen3.cmake)

