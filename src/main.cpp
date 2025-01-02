#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

Graphic* graphic;
int graphicIndex = 0;
bool updateGraphic = true;

bool polygonMode = false;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

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
    const float cameraSpeed = 0.05f;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_W:
            {
                cameraPos += cameraSpeed * cameraFront;
            } break;
            case GLFW_KEY_S:
            {
                cameraPos -= cameraSpeed * cameraFront;
            } break;
            case GLFW_KEY_A:
            {
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            } break;
            case GLFW_KEY_D:
            {
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

int main()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
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

    /*
    // Camera position
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

    // Camera Direction
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);

    // Camera Right Axis
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRightAxis = glm::normalize(glm::cross(cameraUp, cameraDirection));

    // Camera Up Axis
    glm::vec3 cameraUpAxis = glm::cross(cameraDirection, cameraRight);
    */

    Shader shader;
    VBO vbo;
    VAO vao;
    EBO ebo;
    
    Texture container(TEXTURE_FILES[0]);
    Texture face(TEXTURE_FILES[1], true, true);

    // Set user inputs
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processKeyPress);

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

        if (graphicIndex == 11)
        {
            const float radius = 10;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            glm::mat4 view = glm::mat4(1.0f);
            /*
            view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),  // Start
                               glm::vec3(0.0f, 0.0f, 0.0f),  // Target
                               glm::vec3(0.0f, 1.0f, 0.0f)); // Up
            */
            /*
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
            */
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            shader.setMat4("view", view);

            for (int i = 0; i < 10; ++i)
            {
                glm::vec3 position = CUBE_POSITIONS[i];
                glm::mat4 model = glm::mat4(1.0f);
                float angle = 20.0f * i;
                model = glm::translate(model, position);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 3.0f, 0.5f));
                shader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, graphic->numVertexPoints);
            }
        }
        else if (ebo.isLoaded())
        {
            glDrawElements(GL_TRIANGLES, graphic->numVertexPoints, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, graphic->numVertexPoints);
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
