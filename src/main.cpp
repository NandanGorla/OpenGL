#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include "../Header/shaderClass.h"
#include "../Header/VAO.h"
#include "../Header/VBO.h"
#include "../Header/EBO.h"
#include "../Header/Texture.h"

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

GLuint indices[] =
{
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
};

int main()
{
    //Initialize GLFW
    glfwInit();

    //Decide what version of OpenGL to use in GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    //CORE profiles for GLFW - used for get modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //creat a GLFW window object
    GLFWwindow* window = glfwCreateWindow(800,800,//Height and width of window
                                         "Astros Engine", //Name of the window
                                         NULL,NULL);
    
    //Error check if window fails to create
    if (window == NULL)
    {
        std::cerr << "Create Window Failed\n";
        glfwTerminate();
        return -1;
    }
    //Introduce the window to current context
    glfwMakeContextCurrent(window);
    //Load GLAD so it configures OpenGL
    gladLoadGL();

    //Specify viewport of OpenGL in window
    glViewport(0,0,800,800);
    
    Shader shaderProgram("Default.vert","Default.frag");
    
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indices,sizeof(indices));
    
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    GLuint uniID =glGetUniformLocation(shaderProgram.ID,"scale");
    
    //Textures
    // int widthImg, heightImg,numColCh;
    // stbi_set_flip_vertically_on_load(true); 
    // unsigned char* bytes = stbi_load("Pop-Cat-Playful-Gesture-PNG-thumb.png",&widthImg,&heightImg,&numColCh,STBI_rgb_alpha);
    // if (!bytes) {
    //     std::cerr << "Failed to load texture image! (check working directory)" << std::endl;
    // } else {
    //     std::cout << "Loaded image: " << widthImg << "x" << heightImg << ", channels: " << numColCh << std::endl;
    // }
    // GLuint texture;
    // glGenTextures(1,&texture);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D,texture);
    //
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    //
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    // glGenerateMipmap(GL_TEXTURE_2D);
    //
    // stbi_image_free(bytes);
    // glBindTexture(GL_TEXTURE_2D,0);
    //
    // GLuint tex0uni = glGetUniformLocation(shaderProgram.ID,"tex0");
    // shaderProgram.Activete();
    // glUniform1i(tex0uni,0);
    Texture popCat("Pop-Cat-Playful-Gesture-PNG-thumb.png",GL_TEXTURE_2D,GL_TEXTURE0,GL_RGBA,GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram,"tex0",0);
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activete();
        glUniform1f(uniID,0.5f);
        popCat.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        //Takes care of all events in GLFW
        glfwPollEvents();
    }

    //Delete all objects created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();
    shaderProgram.Delete();
    //Destroyes the window object to prevent leak
    glfwDestroyWindow(window);
    
    //Terminates GLFW from memory
    glfwTerminate();
    
    return 0;
}