#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <lighting/Constants.hpp>

static constexpr float WIDTH  = 800;
static constexpr float HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Keyboard variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Mouse variables
const float MOUSE_SENSITIVITY = 0.1f;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;

void handleCameraNavigation(int key, int action)
{
    float cameraSpeed = 100.0f * deltaTime;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_W:
            {
                camera.updatePosition(-cameraSpeed, 'y');
            } break;
            case GLFW_KEY_S:
            {
                camera.updatePosition(cameraSpeed, 'y');
            } break;
            case GLFW_KEY_A:
            {
                camera.updatePosition(-cameraSpeed, 'x');
            } break;
            case GLFW_KEY_D:
            {
                camera.updatePosition(cameraSpeed, 'x');
            } break;
            case GLFW_KEY_Q:
            {
                camera.updatePosition(-cameraSpeed, 'z');
            } break;
            case GLFW_KEY_E:
            {
                camera.updatePosition(cameraSpeed, 'z');
            } break;
            default: break;
        }
    }
}

void processKeyPress(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    handleCameraNavigation(key, action);
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window, true); 
            } break;
            default: break;
        }
    }
}

void processCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{   
    float xOffset = (xPos - lastX) * MOUSE_SENSITIVITY;
    float yOffset = (yPos - lastY) * MOUSE_SENSITIVITY;
    lastX = xPos;
    lastY = yPos;
    camera.updateAngle(xOffset, yOffset);
}

void processMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.updateZoom((float) yOffset);
}

struct Entity
{
    Shader shader;
    VAO vao;
    VBO vbo;
    // EBO ebo;
    // Texture* textures;
    unsigned int numVertices;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view  = glm::mat4(1.0f);
    glm::mat4 proj  = glm::mat4(1.0f);
};

int main()
{
    // Make window
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL [Lighting]", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Set user inputs
    // glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processKeyPress);
    glfwSetCursorPosCallback(window, processCursorPosCallback);
    glfwSetScrollCallback(window, processMouseScrollCallback);

    Entity cube;
    Entity light;

    // Shader
    cube.shader.load("shaders/colors/shader.vert", "shaders/colors/shader.frag");
    light.shader.load("shaders/basic_lighting/shader.vert", "shaders/basic_lighting/lightShader.frag");
    
    // Vertex buffer object
    cube.vbo.load(CUBE_VERTICES, sizeof(CUBE_VERTICES));
    cube.numVertices = 36;

    light.vbo.load(CUBE_VERTICES, sizeof(CUBE_VERTICES));
    light.numVertices = 36;

    // Vertex attributes
    cube.vao.load({ 0, 3, 3 * sizeof(float), 0 });
    light.vao.load({ 0, 3, 3 * sizeof(float), 0 });

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable 3D
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear screen using clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw cube
        cube.shader.use();

        vec3 objColor = {1.0f, 0.5f, 0.31f};
        vec3 lightColor = {1.0f, 1.0f, 1.0f};
        cube.shader.setVec3("objectColor", objColor);
        cube.shader.setVec3("lightColor", lightColor);

        cube.model = glm::mat4(1.0f);
        cube.shader.setMat4("model", cube.model);
        camera.setCamera(cube.shader, WIDTH, HEIGHT);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw light
        light.shader.use();
        
        light.model = glm::mat4(1.0f);
        light.model = glm::translate(light.model, glm::vec3(1.2f, 1.0f, 2.0f));
        light.model = glm::scale(light.model, glm::vec3(0.2f));
        light.shader.setMat4("model", light.model);
        camera.setCamera(light.shader, WIDTH, HEIGHT);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Buffer swapping
        glfwSwapBuffers(window);

        // Event handling
        glfwPollEvents();
    }
    cube.vbo.del();
    cube.vao.del();
    return 0;
}
