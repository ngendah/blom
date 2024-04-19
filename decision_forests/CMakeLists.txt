include(generate_cpp_from_protos.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(utils)
add_subdirectory(cart)
add_subdirectory(dataset)
add_subdirectory(metric)

