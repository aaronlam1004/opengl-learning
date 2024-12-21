#include "Buffers.hpp"
#include <iostream>

// Vertex buffer object
VBO::VBO()
{
    glGenBuffers(1, &id);
}

void VBO::load(const float vertices[], const unsigned int numVertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, numVertices, vertices, GL_STATIC_DRAW);
}

void VBO::del()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glDeleteBuffers(1, &id);
}

// Vertex array object
VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::load(const VertexAttribute& attribute)
{
    glBindVertexArray(id);
    glVertexAttribPointer(attribute.location,
                          attribute.numValues,
                          GL_FLOAT,
                          GL_FALSE,
                          attribute.totalSize,
                          (void*) attribute.start);
    glEnableVertexAttribArray(attribute.location);
}

void VAO::del()
{
    glDeleteVertexArrays(1, &id);
}

// Element buffer object
EBO::EBO()
{
    glGenBuffers(1, &id);
}

void EBO::load(const unsigned int indices[], const unsigned int numIndices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices, indices, GL_STATIC_DRAW);
}

void EBO::del()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glDeleteBuffers(1, &id);
}
