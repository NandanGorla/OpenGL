cmake_minimum_required(VERSION 3.20)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
configure_file(${CMAKE_SOURCE_DIR}/Resource/Shaders/Default.vert ${CMAKE_BINARY_DIR}/Default.vert COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resource/Shaders/Default.frag ${CMAKE_BINARY_DIR}/Default.frag COPYONLY)

add_executable(OpenGL src/main.cpp src/glad.c
        Header/main.h
        Header/shaderClass.h
        src/shaderClass.cpp
        Header/VBO.h
        src/VBO.cpp
        src/EBO.cpp
        Header/EBO.h
        src/VAO.cpp
        Header/VAO.h
        src/stb.cpp
        src/Texture.cpp
        Header/Texture.h)

target_link_libraries(OpenGL PRIVATE glfw opengl32)