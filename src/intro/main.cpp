#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <intro/Graphics.hpp>
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

// Graphic navigation
Graphic* graphic;
int graphicIndex = 0;
bool updateGraphic = true;

// Polygon mode
bool polygonMode = false;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Keyboard variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Mouse variables
const float MOUSE_SENSITIVITY = 0.1f;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void handleGraphicNavigation(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_RIGHT:
            {
                graphicIndex++;
                if (graphicIndex >= NUM_GRAPHICS) graphicIndex = 0;
                updateGraphic = true;
            } break;
            case GLFW_KEY_LEFT:
            {
                graphicIndex--;
                if (graphicIndex < 0) graphicIndex = (NUM_GRAPHICS - 1);
                updateGraphic = true;
            } break;
            default: break;
        }
    }
}

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
    handleGraphicNavigation(key, action);
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window, true); 
            } break;
            case GLFW_KEY_TAB:
            {
                if (polygonMode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                polygonMode = !polygonMode;
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

int main()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL [Intro]", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    Shader shader;
    VBO vbo;
    VAO vao;
    EBO ebo;
    
    Texture container(TEXTURE_FILES[0]);
    Texture face(TEXTURE_FILES[1], true, true);

    // Set user inputs
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processKeyPress);
    glfwSetCursorPosCallback(window, processCursorPosCallback);
    glfwSetScrollCallback(window, processMouseScrollCallback);

    // Set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    while (!glfwWindowShouldClose(window))
    {
        // Input processing
        if (updateGraphic)
        {
            graphic = loadGraphic(graphicIndex, vbo, vao, ebo, shader);
            updateGraphic = false;
        }

        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (graphic->enableZBuffer)
        {
            // Enable 3D
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        
        glClear(GL_COLOR_BUFFER_BIT);

        // Textures
        if (graphic->addTextures != nullptr)
        {
            Texture textures[] = {
                container, face
            };
            graphic->addTextures(shader, textures);
        }

        // Shaders
        shader.use();
        if (graphic->update != nullptr)
        {
            graphic->update(shader);
        }

        // Camera
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        if (graphicIndex == 11)
        {
            const float radius = 10;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            camera.setTempView(shader, glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f));
            camera.setTempPerspective(shader, 45.0f, WIDTH, HEIGHT);
        }
        else
        {
            camera.setCamera(shader, WIDTH, HEIGHT);
        }
        
        // Draw
        if (graphic->draw != nullptr)
        {
            graphic->draw(graphic, shader);
        }
        
        // Event handling and buffer swapping
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vbo.del();
    vao.del();
    ebo.del();
    
    glfwTerminate();
    return 0;
}
