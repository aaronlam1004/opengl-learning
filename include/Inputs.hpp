#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <Logger.hpp>
#include <Scene.hpp>
#include <Camera.hpp>

extern const float WIDTH;
extern const float HEIGHT;

extern int index;
extern int sceneIndex;

extern Scene scenes[];
extern Scene* currentScene;

extern Camera camera;
extern bool freeCamera;

bool isPolygonMode = true;

bool firstMouse = false;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;

const float MOUSE_SENS = 0.1;

void processFramebufferResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processSceneNavigationKeyPress(int key)
{
    switch (key)
    {
        case GLFW_KEY_F1:
        {
            index = 0;
            currentScene = &scenes[0];
            setupScene(*currentScene);
        } break;
        case GLFW_KEY_F2:
        {
            index = 0;
            currentScene = &scenes[1];
            setupScene(*currentScene);
        } break;
        default: break;
    }
}

void processCameraKeyPress(int key)
{
    if (freeCamera)
    {
        switch (key)
        {
            case GLFW_KEY_W:
            {
                camera.updateViewPosition(glm::vec3(0.0f, 0.0f, 0.2f));
            } break;
            case GLFW_KEY_S:
            {
                camera.updateViewPosition(glm::vec3(0.0f, 0.0f, -0.2f));
            } break;
            case GLFW_KEY_A:
            {
                camera.updateViewPosition(glm::vec3(-0.2f, 0.0f, 0.0f));
            } break;
            case GLFW_KEY_D:
            {
                camera.updateViewPosition(glm::vec3(0.2f, 0.0f, 0.0f));
            } break;
            case GLFW_KEY_Q:
            {
                camera.updateViewPosition(glm::vec3(0.0f, -0.2f, 0.0f));
            } break;
            case GLFW_KEY_E:
            {
                camera.updateViewPosition(glm::vec3(0.0f, 0.2f, 0.0f));
            } break;
            default: break;
        }
    }
}

void processKeyPress(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window, true);
            } break;
            case GLFW_KEY_RIGHT:
            {
                index++;
                index %= currentScene->count;
            } break;
            case GLFW_KEY_LEFT:
            {
                index--;
                if (index < 0)
                {
                    index = currentScene->count - 1;
                }
            } break;
            case GLFW_KEY_TAB:
            {
                isPolygonMode = !isPolygonMode;
                if (isPolygonMode)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                else
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
            } break;
            default: break;
        }
        processSceneNavigationKeyPress(key);
        processCameraKeyPress(key);
    }
}

void processMouseMove(GLFWwindow* window, double xPos, double yPos)
{
    if (freeCamera)
    {
        if (firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        float xOffset = (xPos - lastX) * MOUSE_SENS;
        float yOffest = (yPos - lastY) * MOUSE_SENS;
        lastX = xPos;
        lastY = yPos;
        camera.updateViewAngle(xOffset, yOffest);
    }
}

void processMouseScroll(GLFWwindow* window, double xOffset, double yOffset)
{
    if (freeCamera)
    {
        camera.updateZoom((float) yOffset);
    }
}
