#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Resources.hpp"
#include <iostream>

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
    const char* textureFile;
};

const Asset ASSETS[] = {
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        SHADER_FILES[0],
        nullptr,
        0,
        nullptr,
    },
    {
        SQUARE_VERTICES,
        sizeof(SQUARE_VERTICES),
        SHADER_FILES[0],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        nullptr
    },
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        SHADER_FILES[1],
        nullptr,
        0,
        nullptr
    },
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        SHADER_FILES[2],
        nullptr,
        0,
        nullptr
    },
    {
        COLORED_TRIANGLE_VERTICES,
        sizeof(COLORED_TRIANGLE_VERTICES),
        SHADER_FILES[3],
        nullptr,
        0,
        nullptr
    },
    {
        CONTAINER_VERTICES,
        sizeof(CONTAINER_VERTICES),
        SHADER_FILES[4],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        TEXTURE_FILES[0]
    }
};

#define NUM_ASSETS sizeof(ASSETS) / sizeof(Asset)

void loadVertexAttributes(int index, VAO& vao)
{
    switch (index)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        {
            unsigned int totalSize = 3 * sizeof(float); // pos (3)
            vao.load({ 0, 3, totalSize, 0 }); // pos (xyz)
        } break;
        case 4:
        {
            unsigned int totalSize = 6 * sizeof(float); // pos (3) + color (3)
            vao.load({ 0, 3, totalSize, 0 }); // pos (xyz)
            vao.load({ 1, 3, totalSize, 3 * sizeof(float) }); // color (rgb)
        } break;
        case 5:
        {
            unsigned int totalSize = 8 * sizeof(float); // pos (3) + color (3) + texture coords (2)
            vao.load({ 0, 3, totalSize, 0 }); // pos (xyz)
            vao.load({ 1, 3, totalSize, 3 * sizeof(float) }); // color (rgb)
            vao.load({ 2, 2, totalSize, 6 * sizeof(float) }); // texture coords (xy)
        } break;
        default: break;
    }
}


void loadAsset(unsigned int index, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader, Texture& texture)
{
    if (index < NUM_ASSETS)
    {
        Asset asset = ASSETS[index];
        
        // Shader
        shader.load(asset.shaderFiles[0], asset.shaderFiles[1]);
        
        // Vertex buffer object
        vbo.load(asset.vertices, asset.numVertices);

        // Vertex array object
        loadVertexAttributes(index, vao);

        // Element buffer object
        ebo.load(asset.indices, asset.numIndices);

        // Texture
        if (asset.textureFile != nullptr)
        {
            texture.load(asset.textureFile);
        }
    }
}
