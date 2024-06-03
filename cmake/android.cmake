set(blom_BUILD_TESTS OFF)
if(NOT PROTOC_COMPILER)
  include(${PROJECT_GENERATED_CMAKE_DIR}/ProtoBufConfig.cmake)
  set(
    PROTOC_COMPILER
    "${PROJECT_NAME}::protoc"
    CACHE
    FILEPATH
    ""
  )
endif()
add_subdirectory(third_party)
add_subdirectory(decision_forests)

