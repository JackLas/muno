# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

set(SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE rtmidi sfml-graphics sfml-window)