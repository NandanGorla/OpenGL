//
// Created by gnand on 19/09/2026.
//

#include "Header/EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,indices,GL_STATIC_DRAW);
}

void EBO::Bind()
{
    glGenBuffers(GL_ELEMENT_ARRAY_BUFFER,&ID);
}

void EBO::Unbind()
{
    glGenBuffers(GL_ELEMENT_ARRAY_BUFFER,nullptr);
}

void EBO::Delete()
{
    glDeleteBuffers(1,&ID);
}
