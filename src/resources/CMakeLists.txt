# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

set(COMPONENT_NAME muno-resources)

set(GEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/generated)
set(SRC ${GEN_OUTPUT_DIR}/Resources.cpp)
set(GENERATED_SRC ${SRC})
set(INPUT_SRC_TEMPLATE ${CMAKE_CURRENT_LIST_DIR}/src/Resources.gen)

add_custom_command(
    OUTPUT ${GENERATED_SRC} 
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${GEN_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN_OUTPUT_DIR}
    COMMAND ${MUNO_RES_GEN_BIN} ${INPUT_SRC_TEMPLATE} ${GENERATED_SRC} 
    DEPENDS ${MUNO_RES_GEN_TARGET} ${INPUT_SRC_TEMPLATE}
    COMMENT "Generating embedded resources into: ${SRC}"
)

add_library(${COMPONENT_NAME} STATIC ${SRC})
target_link_libraries(${COMPONENT_NAME} PUBLIC sfml-system)
target_include_directories(${COMPONENT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
