// Created by gnand on 26/09/2026.
#include <iostream>
#include <Texture.h>

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
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
    glBindTexture(GL_TEXTURE_2D,ID);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D,0);
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
    glBindTexture(GL_TEXTURE_2D,ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::Delete()
{
    glDeleteTextures(1,&ID);
}