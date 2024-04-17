function(generate_cpp_from_protos PROTO_GLOB INPUT_DIR)
  set(PROTOC_CMD ${protobuf_BINARY_DIR}/protoc)
  set(OUTPUT_DIR ${INPUT_DIR})

  file(GLOB_RECURSE PROTO_FILES RELATIVE ${INPUT_DIR} ${PROTO_GLOB})

  foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)

    add_custom_command(
      OUTPUT ${OUTPUT_DIR}/${PROTO_NAME}.pb.h ${OUTPUT_DIR}/${PROTO_NAME}.pb.cc
      COMMAND ${PROTOC_CMD} -I=${INPUT_DIR} --cpp_out=${OUTPUT_DIR} ${INPUT_DIR}/${PROTO_FILE}
      DEPENDS "${PROTO_FILE}" "${PROTOC_CMD}"
      VERBATIM
    )
  endforeach()
endfunction()


