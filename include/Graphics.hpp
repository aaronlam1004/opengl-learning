#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Constants.hpp"
#include <iostream>

#define MAX_NUM_ATTRIBUTES 3
#define MAX_NUM_TEXTURES 2

struct Graphic
{
    // Vertices
    float* vertices;
    unsigned int numVertices;
    unsigned int attributesPerVertex[MAX_NUM_ATTRIBUTES] = {0};
    unsigned int numVertexPoints;

    // Shader
    const char** shaderFiles;

    // Indices
    unsigned int* indices;
    unsigned int numIndices;

    // Textures
    void (*addTextures)(Shader& shader, Texture* textures);

    // Update
    void (*update)(Shader& shader);

    // Depth z-buffer
    bool enableZBuffer;
};

const Graphic GRAPHICS[] = {
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        { 3 }, // aPos(xyz)
        3, // (1 triangle == 3 points)
        SHADER_FILES[0],
        nullptr,
        0,
        nullptr,
        nullptr,
        false
    },
    {
        SQUARE_VERTICES,
        sizeof(SQUARE_VERTICES),
        { 3 }, // aPos(xyz)
        6, // (1 square == 2 triangles == 6 points)
        SHADER_FILES[0],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        nullptr,
        nullptr,
        false
    },
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        { 3 }, // aPos(xyz)
        3, // (1 triangle == 3 points)
        SHADER_FILES[1],
        nullptr,
        0,
        nullptr,
        nullptr,
        false
    },
    {
        TRIANGLE_VERTICES,
        sizeof(TRIANGLE_VERTICES),
        { 3 }, // aPos(xyz)
        3, // (1 triangle == 3 points)
        SHADER_FILES[2],
        nullptr,
        0,
        nullptr,
        updateGreenTriangle,
        false
    },
    {
        COLORED_TRIANGLE_VERTICES,
        sizeof(COLORED_TRIANGLE_VERTICES),
        { 3, 3 }, // aPos(xyz), aColor(rgb),
        3, // (1 triangle == 3 points)
        SHADER_FILES[3],
        nullptr,
        0,
        nullptr,
        nullptr,
        false
    },
    {
        CONTAINER_VERTICES,
        sizeof(CONTAINER_VERTICES),
        { 3, 3, 2 }, // aPos(xyz), aColor(rgb), aTexCoord(xy)
        6, // (1 square == 2 triangles == 6 points)
        SHADER_FILES[4],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        addBaseContainerTexture,
        nullptr,
        false
    },
    {
        CONTAINER_VERTICES,
        sizeof(CONTAINER_VERTICES),
        { 3, 3, 2 }, // aPos(xyz), aColor(rgb), aTexCoord(xy)
        6, // (1 square == 2 triangles == 6 points)
        SHADER_FILES[5],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        addBaseContainerTexture,
        nullptr,
        false
    },
    {
        CONTAINER_VERTICES,
        sizeof(CONTAINER_VERTICES),
        { 3, 3, 2 }, // aPos(xyz), aColor(rgb), aTexCoord(xy)
        6, // (1 square == 2 triangles == 6 points)
        SHADER_FILES[6],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        addBaseContainerTexture,
        nullptr,
        false
    },
    {
        TEXTURED_CONTAINER_VERTICES,
        sizeof(TEXTURED_CONTAINER_VERTICES),
        { 3, 2 }, // aPos(xyz), aTexCoord(xy)
        6, // (1 square == 2 triangles == 6 points)
        SHADER_FILES[7],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        addMixedContainerTextures,
        updateContainerRotate,
        false
    },
    {
        TEXTURED_CONTAINER_VERTICES,
        sizeof(TEXTURED_CONTAINER_VERTICES),
        { 3, 2 }, // aPos(xyz), aTexCoord(xy)
        6, // (1 square == 2 triangles == 6 points)
        SHADER_FILES[8],
        SQUARE_INDICES,
        sizeof(SQUARE_INDICES),
        addMixedContainerTextures,
        updateContainerPerspective,
        false
    },
    {
        TEXTURED_CUBE_VERTICES,
        sizeof(TEXTURED_CUBE_VERTICES),
        { 3, 2 }, // aPos(xyz), aTexCoord(xy)
        36, // (6 sides == 6 squares == 12 triangles == 36 points)
        SHADER_FILES[8],
        nullptr,
        0,
        addMixedContainerTextures,
        updateContainerCubeRotation,
        true
    },
    {
        TEXTURED_CUBE_VERTICES,
        sizeof(TEXTURED_CUBE_VERTICES),
        { 3, 2 }, // aPos(xyz), aTexCoord(xy)
        36, // (6 sides == 6 squares == 12 triangles == 36 points)
        SHADER_FILES[8],
        nullptr,
        0,
        addMixedContainerTextures,
        updateContainerPerspective,
        true
    }
};

#define NUM_GRAPHICS sizeof(GRAPHICS) / sizeof(Graphic)

void loadVertexAttributes(unsigned int numAttributesPerVertex[MAX_NUM_ATTRIBUTES], VAO& vao)
{
    unsigned int attrIndex = 0;
    unsigned int totalSize = 0;
    while (attrIndex < MAX_NUM_ATTRIBUTES && numAttributesPerVertex[attrIndex] != 0)
    {
        totalSize += numAttributesPerVertex[attrIndex] * sizeof(float);
        attrIndex++;
    }

    unsigned int start = 0;
    attrIndex = 0;
    while (attrIndex < MAX_NUM_ATTRIBUTES && numAttributesPerVertex[attrIndex] != 0)
    {   
        unsigned int numAttrPerProp = numAttributesPerVertex[attrIndex];
        if (attrIndex > 0)
        {
            start += numAttributesPerVertex[attrIndex - 1] * sizeof(float);
        }
        vao.load({ attrIndex, numAttrPerProp, totalSize, start });
        attrIndex++;
    }
}


Graphic* loadGraphic(unsigned int index, VBO& vbo, VAO& vao, EBO& ebo, Shader& shader)
{
    if (index < NUM_GRAPHICS)
    {
        Graphic graphic = GRAPHICS[index];
        
        // Shader
        shader.load(graphic.shaderFiles[0], graphic.shaderFiles[1]);
        
        // Vertex buffer object
        vbo.load(graphic.vertices, graphic.numVertices);

        // Vertex array object
        loadVertexAttributes(graphic.attributesPerVertex, vao);

        // Element buffer object
        ebo.load(graphic.indices, graphic.numIndices);

        return const_cast<Graphic*>(&GRAPHICS[index]);
    }
    return nullptr;
}
