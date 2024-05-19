function(blom_test_target target)
  add_custom_command(
    TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target}> "${PROJECT_BINARY_DIR}/tests/${target}"
    BYPRODUCTS "${PROJECT_BINARY_DIR}/tests/${target}"
    COMMENT "Created ${PROJECT_BINARY_DIR}/tests/${target}"
  )
endfunction()
