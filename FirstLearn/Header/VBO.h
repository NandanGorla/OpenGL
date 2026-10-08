// Created by gnand on 19/09/2026.
#pragma once

#ifndef OPENGL_VBO_H
#define OPENGL_VBO_H

#include <glad/glad.h>
#include "glm/glm.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
    
};

class VBO
{
public:
    GLuint ID{};
    VBO(std::vector<Vertex>& vertices);
    void Bind();
    void Unbind();
    void Delete();
};

#endif //OPENGL_VBO_H