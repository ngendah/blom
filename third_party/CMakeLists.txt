set(FETCHCONTENT_POPULATE_EXTERNAL_PROJECT ON)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
include(abseil.cmake)
include(googletest.cmake)
include(farmhash.cmake)
include(boost_math.cmake)
include(protobuf.cmake)
include(eigen3.cmake)

