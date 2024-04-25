include(CCMakeProtos.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(utils)
add_subdirectory(cart)
add_subdirectory(dataset)
add_subdirectory(metric)
add_subdirectory(model)
add_subdirectory(learner)
