#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Logger.hpp>
#include <Inputs.hpp>
#include <Scene.hpp>
#include <Camera.hpp>

#include <Scene0/Scene.hpp>
#include <Scene1/Scene.hpp>

static const float WIDTH = 800.0f;
static const float HEIGHT = 600.0f;

Camera camera(WIDTH, HEIGHT);
Logger logger;

int index = 0;
bool freeCamera = false;

Scene scenes[] = {
    SCENE_0,
    SCENE_1
};
Scene* currentScene = &scenes[0];

int main(int argc, char* argv[])
{
    // GLFW Window
    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        LOG_ERROR("Failed to create GLFW window\n");
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        LOG_ERROR("Failed to initialize GLAD for OpenGL\n");
        return -1;
    }

    // Inputs
    glfwSetFramebufferSizeCallback(window, processFramebufferResize);
    glfwSetKeyCallback(window, processKeyPress);
    glfwSetCursorPosCallback(window, processMouseMove);
    glfwSetScrollCallback(window, processMouseScroll);

    // Setup
    setupScene(*currentScene);
    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    while (!glfwWindowShouldClose(window))
    {
        renderScene(*currentScene, index);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
