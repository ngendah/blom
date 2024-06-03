add_subdirectory(third_party)
export(
  TARGETS protoc
  NAMESPACE "${PROJECT_NAME}::"
  FILE "${PROJECT_GENERATED_CMAKE_DIR}/ProtoBufConfig.cmake"
)
set(
  PROTOC_COMPILER
  protoc
  CACHE
  FILEPATH
  ""
)
if(blom_BUILD_TESTS)
  enable_testing()
  add_custom_target(
    test_data ALL
    DEPENDS testing_data
  )
  add_custom_command(
    OUTPUT testing_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/testing_data
    ${PROJECT_BINARY_DIR}/testing_data
  )
  set_property(
    TARGET test_data
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${PROJECT_BINARY_DIR}/testing_data
  )
endif()
add_subdirectory(decision_forests)
if(blom_BUILD_EXAMPLE)
  add_subdirectory(example)
endif ()

