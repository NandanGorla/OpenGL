// Created by gnand on 17/09/2026.
#pragma once

#ifndef OPENGL_SHADERCLASS_H
#define OPENGL_SHADERCLASS_H

#include <glad/glad.h>
#include <string>
#include <sstream>

std::string get_file_contents(const char* filename);
class Shader
{
public:
    GLuint ID;
    int success;
    char infoLog[512];
    Shader(const char* vertexFile,const char* fragmentFile);
    void Activete();
    void Delete();
private:
    void compileError(unsigned int shader,const char* type);
};

#endif //OPENGL_SHADERCLASS_H