# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

project(muno LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MUNO_RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)

add_subdirectory(deps)
add_subdirectory(tools/cpp-resources-generator)
add_subdirectory(src)
