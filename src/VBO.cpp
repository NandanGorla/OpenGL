//
// Created by gnand on 19/09/2026.
//
#include "Header/VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ARRAY_BUFFER,ID);
    glBufferData(GL_ARRAY_BUFFER,size,vertices,GL_STATIC_DRAW);
}

void VBO::Bind()
{
    glGenBuffers(GL_ARRAY_BUFFER,&ID);
}

void VBO::Unbind()
{
    glGenBuffers(GL_ARRAY_BUFFER,nullptr);
}

void VBO::Delete()
{
    glDeleteBuffers(1,&ID);
}
