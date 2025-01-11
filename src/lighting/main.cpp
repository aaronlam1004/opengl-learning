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

        vec3 objColor = {1.0f, 0.5f, 0.31f};
        vec3 lightColor = {1.0f, 1.0f, 1.0f};
        cube.shader.setVec3("objectColor", objColor);
        cube.shader.setVec3("lightColor", lightColor);

        cube.model = glm::mat4(1.0f);
        cube.model = glm::translate(cube.model, glm::vec3(-0.5f, 0.0f, 2.0f));
        cube.model = glm::rotate(cube.model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        cube.view = glm::mat4(1.0f);
        cube.view = glm::translate(cube.view, glm::vec3(0.0f, 0.0f, -5.0f));
        cube.proj = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);

        cube.shader.setMat4("model", cube.model);
        cube.shader.setMat4("view", cube.view);
        cube.shader.setMat4("projection", cube.proj);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw light
        light.shader.use();
        
        light.model = glm::mat4(1.0f);
        light.model = glm::translate(light.model, glm::vec3(1.0f, 1.0f, 2.0f));
        light.model = glm::scale(light.model, glm::vec3(0.2f));
        light.view = glm::mat4(1.0f);
        light.view = glm::translate(light.view, glm::vec3(0.0f, 0.0f, -5.0f));
        light.proj = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);

        light.shader.setMat4("model", light.model);
        light.shader.setMat4("view", light.view);
        light.shader.setMat4("projection", light.proj);

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
