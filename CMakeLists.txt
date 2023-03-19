cmake_minimum_required(VERSION 3.12)

set(name_project Game)
project(${name_project})

add_subdirectory(src)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/opengl32.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/SDL2 DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/glm DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/SDL2.lib DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/SDL2main.lib DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY libs/OpenGL32.lib DESTINATION ${CMAKE_BINARY_DIR})
