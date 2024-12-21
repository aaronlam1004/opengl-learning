#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Constants.hpp"
#include <iostream>

static constexpr unsigned int NUM_RESOURCES = 1;

struct Resource
{
    // Vertices
    float* vertices;
    unsigned int numVertices;

    // Shader
    const char** shaderFiles;

    // Indices
    float* indices;
    unsigned int numIndices;

    // Texture
    const char** textureFiles;
};

const Resource RESOURCES[] = {
    {
        TRIANGLE,
        sizeof(TRIANGLE),
        SHADER_FILES[0],
        nullptr,
        0,
        nullptr
    }
};

void loadVertexAttributes(int index, VAO& vao)
{
    switch (index)
    {
        case 0:
        {
            vao.load({ 0, 3, 3 * sizeof(float), 0 }); // pos
        } break;;
        default: break;
    }
}


void loadResource(unsigned int index, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture)
{
    if (index < NUM_RESOURCES)
    {
        Resource resource = RESOURCES[index];

        // Texture
        // texture = &resource.texture;
        
        // Shader
        shader.load(resource.shaderFiles[0], resource.shaderFiles[1]);
        
        // Vertex buffer object
        vbo.load(resource.vertices, resource.numVertices);

        // Vertex array object
        loadVertexAttributes(index, vao);

        // Element buffer object
        if (resource.indices != nullptr)
        {
        }
    }
}
