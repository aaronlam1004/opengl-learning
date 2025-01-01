#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

int graphicIndex = 0;
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
                graphicIndex++;
                if (graphicIndex >= NUM_GRAPHICS) graphicIndex = 0;
                updateAsset = true;
            } break;
            case GLFW_KEY_LEFT:
            {
                graphicIndex--;
                if (graphicIndex < 0) graphicIndex = (NUM_GRAPHICS - 1);
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


Graphic* graphic;
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

    Shader shader;
    VBO vbo;
    VAO vao;
    EBO ebo;
    
    Texture container;
    container.load(TEXTURE_FILES[0]);

    Texture face;
    face.load(TEXTURE_FILES[1], true, true);

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
            graphic = loadGraphic(graphicIndex, vbo, vao, ebo, shader);
            updateAsset = false;
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
