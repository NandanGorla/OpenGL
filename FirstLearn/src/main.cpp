#define GLM_ENABLE_EXPERIMENTAL
#include <Mesh.h>
#include <iostream>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <stb/stb_image.h>
//
// #include <VAO.h>
// #include <VBO.h>
// #include <EBO.h>
// #include <shaderClass.h>
// #include <Texture.h>
// #include <Camera.h>

//Verticies coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
    Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};


// Indices for vertices order
GLuint indices[]
{
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
    Vertex{glm::vec3(-0.1f,-0.1f, 0.1f)},
    Vertex{glm::vec3(-0.1f,-0.1f,-0.1f)},
    Vertex{glm::vec3( 0.1f,-0.1f,-0.1f)},
    Vertex{glm::vec3( 0.1f,-0.1f, 0.1f)},
    Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
    Vertex{glm::vec3(-0.1f, 0.1f,-0.1f)},
    Vertex{glm::vec3( 0.1f, 0.1f,-0.1f)},
    Vertex{glm::vec3( 0.1f, 0.1f, 0.1f)}
};

GLuint lightIndices[]
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

const unsigned int width{800};
const unsigned int height{800};

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
    GLFWwindow* window
    {
        glfwCreateWindow(width,height,      //Height and width of window
                         "Astros Engine",   //Name of the window
                         nullptr,nullptr)
    };
    
    //Error check if window fails to create
    if (window == nullptr)
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
    glViewport(0,0,width,height);
    
    Texture textures[]
    {
        Texture(RESOURCE_DIR"Textures/container2.png", "diffuse" ,0,GL_RGBA,GL_UNSIGNED_BYTE),
        Texture(RESOURCE_DIR"Textures/container2_specular.png", "specular",1,GL_RED,GL_UNSIGNED_BYTE)
    };
    
    Shader shaderProgram(RESOURCE_DIR"Shaders/Default.vert", RESOURCE_DIR"Shaders/Default.frag");
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh floor(verts,ind,tex);
    
    Shader lightShader(RESOURCE_DIR"Shaders/light.vert",RESOURCE_DIR"Shaders/light.frag");
    std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    // Create light mesh
    Mesh light(lightVerts, lightInd, tex);
    
    glm::vec4 lightColor{glm::vec4(1.0f,1.0f,1.0f,1.0f)};
    
    glm::vec3 lightPos{glm::vec3(0.5f,0.5f,0.5f)};
    glm::mat4 lightModel{glm::mat4(1.0f)};
    lightModel = glm::translate(lightModel,lightPos);
    
    glm::vec3 pyramidPos{glm::vec3(0.0f,0.0f,0.0f)};
    glm::mat4 pyramidModel{glm::mat4(1.0f)};
    pyramidModel = glm::translate(pyramidModel,pyramidPos);
    
    lightShader.Activete();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID,"model"),1,GL_FALSE,glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    shaderProgram.Activete();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"model"),1,GL_FALSE,glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
    
    GLuint uniID =glGetUniformLocation(shaderProgram.ID,"scale");
    
    
    
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.Input(window);
        camera.updateMatrix(45.0f,0.1f,100.0f);
        
        floor.Draw(shaderProgram,camera);
        floor.Draw(lightShader,camera);
        
        glfwSwapBuffers(window);
        //Takes care of all events in GLFW
        glfwPollEvents();
    }

    //Delete all objects created
    shaderProgram.Delete();
    lightShader.Delete();
    //Destroyes the window object to prevent leak
    glfwDestroyWindow(window);
    
    //Terminates GLFW from memory
    glfwTerminate();
    
    return 0;
}