# This file handles building each task as sub-project.
# Each task becomes an independent project in which you can experiment.
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.20)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
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
)

target_compile_definitions(OpenGL PRIVATE RESOURCE_DIR="${CMAKE_SOURCE_DIR}/Resource/")


target_link_libraries(OpenGL PRIVATE
        ${CMAKE_SOURCE_DIR}/Resource/Lib/glfw3.lib
        opengl32
)

# Add tasks subprojects
add_subprojects(${CMAKE_SOURCE_DIR})