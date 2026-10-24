// Created by gnand on 19/09/2026.

#pragma once

#ifndef EBO_H
#define EBO_H

#include <vector>
#include <glad/glad.h>

class EBO
{
public:
    GLuint ID{};
    EBO(std::vector<GLuint>& indices);
    
    void Bind();
    void Unbind();
    void Delete();
};


#endif //OPENGL_EBO_H
