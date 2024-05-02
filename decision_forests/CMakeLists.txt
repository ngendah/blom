include(CCMakeProtos.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(utils)
add_subdirectory(dataset)
add_subdirectory(metric)
add_subdirectory(model)
add_subdirectory(learner)
add_subdirectory(serving)
add_subdirectory(e2e_test_utils)

