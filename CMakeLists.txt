cmake_minimum_required(VERSION 3.20)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Resource)
include_directories(${CMAKE_SOURCE_DIR}/Header)

add_executable(OpenGL
        src/main.cpp
        src/glad.c
        src/stb.cpp
        src/VAO.cpp
        src/VBO.cpp
        src/EBO.cpp
        src/shaderClass.cpp
        src/Texture.cpp
        src/Camera.cpp
        Header/Camera.h
)

target_compile_definitions(OpenGL PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/Resource/")


target_link_libraries(OpenGL PRIVATE
        ${CMAKE_SOURCE_DIR}/Resource/Lib/glfw3.lib
        opengl32
)