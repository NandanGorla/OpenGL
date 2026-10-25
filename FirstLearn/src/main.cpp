#define GLM_ENABLE_EXPERIMENTAL

#include <Model.h>
#include <iostream>

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
        
    Shader shaderProgram(RESOURCE_DIR"Shaders/Default.vert", RESOURCE_DIR"Shaders/Default.frag");
    
    glm::vec4 lightColor{glm::vec4(1.0f,1.0f,1.0f,1.0f)};
    
    glm::vec3 lightPos{glm::vec3(0.5f,0.5f,0.5f)};
    glm::mat4 lightModel{glm::mat4(1.0f)};
    lightModel = glm::translate(lightModel,lightPos);
    
    shaderProgram.Activete();
    glUniform4f(glGetUniformLocation(shaderProgram.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
    
    GLuint uniID =glGetUniformLocation(shaderProgram.ID,"scale");
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));
    
    Model model(RESOURCE_DIR"Models/sword/scene.gltf");
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.85f, 0.85f, 0.85f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        camera.Input(window);
        camera.updateMatrix(45.0f,0.1f,100.0f);
        
        model.Draw(shaderProgram,camera);
        
        glfwSwapBuffers(window);
        //Takes care of all events in GLFW
        glfwPollEvents();
    }

    //Delete all objects created
    shaderProgram.Delete();
    //Destroyes the window object to prevent leak
    glfwDestroyWindow(window);
    
    //Terminates GLFW from memory
    glfwTerminate();
    
    return 0;
}