# Copyright (c) 2025 Yevhenii Kryvyi
# SPDX-License-Identifier: MIT

# enable static libs for rtmidi
set(RTMIDI_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# disable rtmidi tests
set(RTMIDI_BUILD_TESTING OFF CACHE BOOL "" FORCE)

# build rtmidi
add_subdirectory(rtmidi)

# enable static libs for sfml
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "" FORCE)

# build sfml
add_subdirectory(sfml)
