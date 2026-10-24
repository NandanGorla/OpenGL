// Created by gnand on 17/09/2026.
#pragma once

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <sstream>
#include <glad/glad.h>

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

#endif //SHADER_CLASS_H