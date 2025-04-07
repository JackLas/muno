# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

project(muno-cpp-resources-generator LANGUAGES CXX)

set(SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

set(MUNO_RES_GEN_TARGET ${PROJECT_NAME} PARENT_SCOPE)
set(MUNO_RES_GEN_BIN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} PARENT_SCOPE)
