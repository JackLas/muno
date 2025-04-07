# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

project(muno LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(deps)
add_subdirectory(src)
