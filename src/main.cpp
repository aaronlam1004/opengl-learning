#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Resources.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

float triangleVertices[] = {
    // aPos (xyz)       // aColor (RGB)
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f
};

float squareVertices[] = {
     0.5f,  0.5f, 0.0f, // top right
     0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,	// top left
};

float containerVertices[] = {
     // aPos (xyz)      // aColor (RGB)   //aTexCoord (xy)
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left 
};

unsigned int squareIndices[] = {
    0, 1, 3, // 1st triangle
    1, 2, 3  // 2nd triangle
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
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
    Texture texture;
    VBO vbo;
    VAO vao;
    EBO ebo;
    loadResource(0, vbo, vao, ebo, shader, texture);
    
    /*
    // Texture
    Texture texture;
    texture.load("resources/textures/container.jpg");

    // Shader
    Shader shader;
    shader.load("shaders/shader.vert", "shaders/shader.frag");
    
    // Setup vertex buffer
    VBO vbo;
    vbo.load(triangleVertices, sizeof(triangleVertices));

    // Setup vertex array object
    VAO vao;
    VAO::VertexAttribute attrPos = {
        0,
        3,
        8 * sizeof(float),
        0
    };
    VAO::VertexAttribute attrColor = {
        1,
        3,
        8 * sizeof(float),
        attrPos.start + (3 * sizeof(float))
    };
    VAO::VertexAttribute attrTexturePos = {
        2,
        2,
        8 * sizeof(float),
        attrColor.start + (3 * sizeof(float))
    };
    vao.load(attrPos);
    vao.load(attrColor);
    vao.load(attrTexturePos);
    */

    // Element buffer objects
    // EBO ebo;
    // ebo.load(squareIndices, sizeof(squareIndices));

    // Set user inputs
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Set clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window))
    {
        // Input processing
        processInput(window);
        
        // Rendering
        glClear(GL_COLOR_BUFFER_BIT);

        // Textures
        // texture.use();

        // Shaders
        shader.use();
        // shader.setInt("ourTexture", 0);
        // float timeVal = glfwGetTime();
        // float green = (sin(timeVal) / 2.0f) / 0.5f;
        // vec4 color = {0.0, green, 0.0, 1.0};
        // shader.setVec4("ourColor", color);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
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
