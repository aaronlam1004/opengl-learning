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

struct Entity
{
    Shader shader;
    VAO vao;
    VBO vbo;
    // EBO ebo;
    // Texture* textures;
    unsigned int numVertices;
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

    Entity cube;
    Entity light;

    // Shader
    cube.shader.load("shaders/colors/shader.vert", "shaders/colors/shader.frag");
    light.shader.load("shaders/colors/shader.vert", "shaders/colors/lightShader.frag");
    
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
        // Clear screen using clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw cube
        cube.shader.use();
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -5.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);

        cube.shader.setMat4("model", model);
        cube.shader.setMat4("view", view);
        cube.shader.setMat4("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw light
        light.shader.use();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));

        light.shader.setMat4("model", model);
        light.shader.setMat4("view", view);
        light.shader.setMat4("projection", projection);

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
