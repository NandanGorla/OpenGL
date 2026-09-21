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

    static void LinkVBO(VBO VBO,GLuint layout);
    void Bind() const;
    static void Unbind();
    void Delete();
};


#endif //OPENGL_VAO_H
