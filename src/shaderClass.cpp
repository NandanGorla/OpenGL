// Created by gnand on 17/09/2026.
#include <iostream>
#include "../Header/shaderClass.h"
#include <fstream>


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

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);
    
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();
    
    //Create Vertex Shader Object and get referance
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Attach vertex shader source to the vertex shader object
    glShaderSource(vertexShader,1,&vertexSource, 0);
    //Compile the vertex shader into machine code
    glCompileShader(vertexShader);
    compileError(vertexShader,"VERTEX");
    
    //Create fragment shader and get referance
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Attach fragment shader source to the fragment shafer object
    glShaderSource(fragmentShader,1,&fragmentSource,0);
    //Compiele the vertex shader into machine code
    glCompileShader(fragmentShader);
    compileError(fragmentShader,"FRAGMENT");
    
    //Make shader progeam object anf get its referance
    ID = glCreateProgram();
    //Attach the vertex and fragment shader to shader program
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);
    //Link all shaders together into the shader program
    glLinkProgram(ID);
    compileError(ID,"PROGRAM");
    
    //Delete now useless vertex and fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activete()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::compileError(unsigned int shader, const char* type)
{
    GLint hasCompiled;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader,GL_COMPILE_STATUS,&hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader,1024,NULL,infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for" << type <<std::endl;
        }
    }else{
        glGetProgramiv(shader,GL_COMPILE_STATUS,&hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader,1024,NULL,infoLog);
            std::cout << "SHADER_LINKING_ERROR for" << type << std::endl;
        }
    }
}
