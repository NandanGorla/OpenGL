//
// Created by gnand on 17/09/2026.
//
#include "Header/shaderClass.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename,std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0,std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0,std::ios::beg);
        in.read(&contents[0],contents.size());
        in.close();
        return (contents);
    }
    throw (errno);
}

shader::shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);
    
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();
    
    //Create Vertex Shader Object and get referance
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Attach vertex shader source to the vertex shader object
    glShaderSource(vertexShader,1,&vertexSource, nullptr);
    //Compile the vertex shader into machine code
    glCompileShader(vertexShader);
    
    //Create fragment shader and get referance
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Attach fragment shader source to the fragment shafer object
    glShaderSource(fragmentShader,1,&fragmentSource,nullptr);
    //Compiele the vertex shader into machine code
    glCompileShader(fragmentShader);
    
    //Make shader progeam object anf get its referance
    ID = glCreateProgram();
    //Attach the vertex and fragment shader to shader program
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);
    //Link all shaders together into the shader program
    glLinkProgram(ID);
    glUseProgram(ID);
    
    //Delete now useless vertex and fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void shader::Activete()
{
    glUseProgram(ID);
}

void shader::Delete()
{
    glDeleteProgram(ID);
}
