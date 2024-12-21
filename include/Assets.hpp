#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Resources.hpp"
#include <iostream>

static constexpr unsigned int NUM_ASSETS = 2;

struct Asset
{
    // Vertices
    float* vertices;
    unsigned int numVertices;

    // Shader
    const char** shaderFiles;

    // Indices
    unsigned int* indices;
    unsigned int numIndices;

    // Texture
    const char** textureFiles;
};


unsigned int TRIANGLE_INDICES[] = { 0, 1, 2 };
const Asset ASSETS[] = {
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        SHADER_FILES[0],
        TRIANGLE_INDICES,
        3,
        nullptr
    },
    {
        SQUARE_VERTICES,
        sizeof(CONTAINER_VERTICES),
        SHADER_FILES[0],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        nullptr
    }
};

void loadVertexAttributes(int index, VAO& vao)
{
    switch (index)
    {
        case 0:
        case 1:
        {
            vao.load({ 0, 3, 3 * sizeof(float), 0 }); // pos
        } break;
        default: break;
    }
}


void loadAsset(unsigned int index, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture)
{
    if (index < NUM_ASSETS)
    {
        Asset asset = ASSETS[index];

        // Texture
        // texture = &asset.texture;
        
        // Shader
        shader.load(asset.shaderFiles[0], asset.shaderFiles[1]);
        
        // Vertex buffer object
        vbo.load(asset.vertices, asset.numVertices);

        // Vertex array object
        loadVertexAttributes(index, vao);

        // Element buffer object
        if (asset.indices != nullptr)
        {
            ebo.load(asset.indices, asset.numIndices);
        }
    }
}
