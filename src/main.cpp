#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Header/shaderClass.h"
#include "Header/VAO.h"
#include "Header/VBO.h"
#include "Header/EBO.h"

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
     0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
     0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
};
GLuint indices[] =
{
    0, 1, 2
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
                                         nullptr,nullptr);
    
    //Error check if window fails to create
    if (window == nullptr)
    {
        std::cerr << "Create Window Failed\n";
        glfwTerminate();
    }
    //Introduce the window to current context
    glfwMakeContextCurrent(window);
    //Load GLAD so it configures OpenGL
    gladLoadGL();

    //Specify viewport of OpenGL in window
    glViewport(0,0,800,800);
    
    
    shader shaderProgram("Default.vert","Default.frag");
    
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices,sizeof(vertices));
    EBO EBO1(indices,sizeof(indices));
    
    VAO1.LinkVBO(VBO1,0);
    VAO1.Unbind();
    VBO::Unbind();
    EBO::Unbind();
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.352f,0.815f,0.223,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activete();
        VAO1.Bind();
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(window);
        //Takes care of all events in GLFW
        glfwPollEvents();
    }

    //Delete all objects created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    //Destroyes the window object to prevent leak
    glfwDestroyWindow(window);
    
    //Terminates GLFW from memory
    glfwTerminate();
    
    return 0;
}