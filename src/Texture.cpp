// Created by gnand on 26/09/2026.
#include <iostream>
#include "../Header/Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;
    int widthImg, heightImg,numColCh;
    stbi_set_flip_vertically_on_load(true); 
    unsigned char* bytes = stbi_load(image,&widthImg,&heightImg,&numColCh,STBI_rgb_alpha);
    if (!bytes) {
        std::cerr << "Failed to load texture image! (check working directory)" << std::endl;
    } else {
        std::cout << "Loaded image: " << widthImg << "x" << heightImg << ", channels: " << numColCh << std::endl;
    }
    glGenTextures(1,&ID);
    glActiveTexture(slot);
    glBindTexture(texType,ID);
    
    glTexParameteri(texType,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(texType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    glTexParameteri(texType,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(texType,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);
    
    stbi_image_free(bytes);
    glBindTexture(texType,0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint uint)
{
    GLuint tex0uni = glGetUniformLocation(shader.ID,uniform);
    shader.Activete();
    glUniform1i(tex0uni,uint);
}

void Texture::Bind()
{
    glBindTexture(type,ID);
}

void Texture::Unbind()
{
    glBindTexture(type,0);
}

void Texture::Delete()
{
    glDeleteTextures(1,&ID);
}