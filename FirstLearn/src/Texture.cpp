// Created by gnand on 26/09/2026.
#include <iostream>
#include <Texture.h>

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
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
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(texType,ID);
    
    glTexParameteri(texType,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    glTexParameteri(texType,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(texType,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);
    
    stbi_image_free(bytes);
    glBindTexture(texType,0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint uint)
{
    GLuint texuni = glGetUniformLocation(shader.ID,uniform);
    shader.Activete();
    glUniform1i(texuni,uint);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
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