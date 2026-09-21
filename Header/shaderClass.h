//
// Created by gnand on 17/09/2026.
//
#pragma once

#ifndef OPENGL_SHADERCLASS_H
#define OPENGL_SHADERCLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

std::string get_file_contents(const char* filename);
class shader
{
public:
    GLuint ID;
    shader(const char* vertexFile,const char* fragmentFile);
    
    void Activete();
    void Delete();
};

#endif //OPENGL_SHADERCLASS_H
