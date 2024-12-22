#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Assets.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

int assetIndex = 0;
bool updateAsset = true;

bool polygonMode = false;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processKeyPress(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window, true); 
            } break;
            case GLFW_KEY_RIGHT:
            {
                assetIndex++;
                if (assetIndex >= NUM_ASSETS) assetIndex = 0;
                updateAsset = true;
            } break;
            case GLFW_KEY_LEFT:
            {
                assetIndex--;
                if (assetIndex < 0) assetIndex = (NUM_ASSETS - 1);
                updateAsset = true;
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

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
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

    Shader shader;
    VBO vbo;
    VAO vao;
    EBO ebo;
    Texture texture;
    texture.load(TEXTURE_FILES[0]);

    // Set user inputs
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, processKeyPress);

    // Set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    while (!glfwWindowShouldClose(window))
    {
        // Input processing
        if (updateAsset)
        {
            loadAsset(assetIndex, vbo, vao, ebo, shader);
            updateAsset = false;
        }
        
        // Rendering
        glClear(GL_COLOR_BUFFER_BIT);

        // Textures
        if (assetIndex == 5 || assetIndex == 6)
        {
            texture.use();
        }

        // Shaders
        shader.use();

        if (assetIndex == 3)
        {
            float timeVal = glfwGetTime();
            float green = (sin(5 * timeVal) * 0.35) + 0.65;
            vec4 color = {0.0, green, 0.0, 1.0};
            shader.setVec4("ourColor", color);
        }

        if (ebo.isLoaded())
        {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);
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
