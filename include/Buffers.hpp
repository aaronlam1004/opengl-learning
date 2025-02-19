#pragma once

#include <glad/glad.h>

// Vertex buffer object
class VBO
{
    public:
        VBO();
        void load(const float vertices[], const unsigned int numVertices);
        void use();
        void del();

    private:
        unsigned int id;
};

// Vertex array object
class VAO
{
    public:
        struct VertexAttribute
        {
            unsigned int index;
            unsigned int numValues;
            unsigned int totalSize;
            unsigned int start;
        };
    
        VAO();
        void load(const VertexAttribute& attribute);
        void use();
        void del();

    private:
        unsigned int id;
};

// Element buffer object
class EBO
{
    public:
        EBO();
        bool isLoaded();
        void load(const unsigned int indices[], const unsigned int numIndices);
        void use();
        void del();
    
    private:
        unsigned int id;
        bool loaded = false;
};
