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
    Shader outliningProgram(RESOURCE_DIR"Shaders/outlining.vert", RESOURCE_DIR"Shaders/outlining.frag");
    
    glm::vec4 lightColor{glm::vec4(1.0f,1.0f,1.0f,1.0f)};
    
    glm::vec3 lightPos{glm::vec3(0.5f,0.5f,0.5f)};
    glm::mat4 lightModel{glm::mat4(1.0f)};
    lightModel = glm::translate(lightModel,lightPos);
    
    shaderProgram.Activete();
    glUniform4f(glGetUniformLocation(shaderProgram.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
    
    GLuint uniID =glGetUniformLocation(shaderProgram.ID,"scale");
    
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    
    Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));
    
    Model model(RESOURCE_DIR"Models/crow/scene.gltf");
    Model outline(RESOURCE_DIR"Models/crow-outline/scene.gltf");
    
    double crntTime{0}, prevTime{0}, timeDiff;
    unsigned int counter{0};
    
    glfwSwapInterval(0);
    
    while (!glfwWindowShouldClose(window))
    {
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;
        if (timeDiff > 1.0 / 30.0)
        {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "Astros Engine" + FPS +"FPS /" + ms + "ms";
            glfwSetWindowTitle(window,newTitle.c_str());
            prevTime = crntTime;
            counter = 0;
            camera.Input(window);
        }
        
        glClearColor(0.85f, 0.85f, 0.85f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        
        camera.updateMatrix(45.0f,0.1f,100.0f);
        
        glStencilFunc(GL_ALWAYS,1,0xFF);
        glStencilMask(0xFF);
        model.Draw(shaderProgram,camera);
        
        glStencilFunc(GL_NOTEQUAL,1,0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        outliningProgram.Activete();
        glUniform1f(glGetUniformLocation(outliningProgram.ID,"outlining"),0.08f);
        outline.Draw(outliningProgram,camera);
        
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS,0,0xFF);
        glEnable(GL_DEPTH_TEST);
        
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