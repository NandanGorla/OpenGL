//
// Created by gnand on 19/09/2026.
//
#pragma once

#ifndef OPENGL_EBO_H
#define OPENGL_EBO_H

#include <glad/glad.h>

class EBO
{
public:
    GLuint ID{};
    EBO(GLuint* indices,GLsizeiptr size);
    
    void Bind();
    static void Unbind();
    void Delete();
};


#endif //OPENGL_EBO_H
