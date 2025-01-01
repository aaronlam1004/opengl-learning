#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float TRIANGLE_VERTICES[] = {
    // aPos(xyz)
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

float COLORED_TRIANGLE_VERTICES[] = {
    // aPos (xyz)       // aColor (RGB)
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f
};

float SQUARE_VERTICES[] = {
     // aPos(xyz)
     0.5f,  0.5f, 0.0f, // top right
     0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,	// top left
};

float CONTAINER_VERTICES[] = {
     // aPos (xyz)      // aColor (RGB)   //aTexCoord (xy)
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left 
};

float TEXTURED_CONTAINER_VERTICES[] = {
     // aPos (xyz)      //aTexCoord (xy)
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
};

unsigned int SQUARE_INDICES[] = {
    0, 1, 3, // 1st triangle
    1, 2, 3  // 2nd triangle
};

float TEXTURED_CUBE_VERTICES[] = {
    // aPos (xyz) // aTexCoord(xy)
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

const char* SHADER_FILES[][2] = {
    { "shaders/hello_triangle/shader.vert", "shaders/hello_triangle/shader.frag" },
    { "shaders/red_triangle/shader.vert", "shaders/red_triangle/shader.frag" },
    { "shaders/shaders_uniform/shader.vert", "shaders/shaders_uniform/shader.frag" },
    { "shaders/shaders_interpolation/shader.vert", "shaders/shaders_interpolation/shader.frag" },
    { "shaders/textures/shader.vert", "shaders/textures/shader.frag" },
    { "shaders/color_mask_textures/shader.vert", "shaders/color_mask_textures/shader.frag" },
    { "shaders/textures_combined/shader.vert", "shaders/textures_combined/shader.frag" },
    { "shaders/transformations/shader.vert", "shaders/transformations/shader.frag" },
    { "shaders/coordinate_systems/shader.vert", "shaders/coordinate_systems/shader.frag" },
};

const char* TEXTURE_FILES[] = {
    "resources/textures/container.jpg",
    "resources/textures/awesomeface.png",
};

void addBaseContainerTexture(Shader& shader, Texture* textures)
{
    textures[0].use(); // Base
}

void addMixedContainerTextures(Shader& shader, Texture* textures)
{
    shader.setInt("containerTexture", 0);
    shader.setInt("faceTexture", 1);
    textures[0].use(); // Base
    textures[1].use(GL_TEXTURE1); // Face
}

void updateGreenTriangle(Shader& shader)
{
    float timeVal = glfwGetTime();
    float green = (sin(5 * timeVal) * 0.35) + 0.65;
    vec4 color = {0.0, green, 0.0, 1.0};
    shader.setVec4("ourColor", color);
}

void updateContainerRotate(Shader& shader)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float) glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("transform", transform);
}

void updateContainerPerspective(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

void updateContainerCubeRotation(Shader& shader)
{
    updateContainerPerspective(shader);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float) glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    shader.setMat4("model", model);
}