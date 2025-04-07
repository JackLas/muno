# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

set(SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PRIVATE rtmidi sfml-graphics sfml-window)