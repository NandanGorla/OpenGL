//
// Created by gnand on 20/09/2026.
//
#pragma once

#ifndef OPENGL_VAO_H
#define OPENGL_VAO_H

#include <glad/glad.h>
#include "Header/VBO.h"

class VAO
{
public:
    GLuint ID{};
    VAO();

    void LinkAttrib(VBO VBO,GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride,void* offset);
    void Bind();
    void Unbind();
    void Delete();
};


#endif //OPENGL_VAO_H
