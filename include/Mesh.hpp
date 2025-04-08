#pragma once

#include <cassert>
#include <vector>
#include <glad/glad.h>
#include <stb_image.h>

#include <Logger.hpp>
#include <Texture.hpp>

class Mesh
{
    public:
        Mesh();
        void load(const std::vector<float> vertices, const std::vector<float> attributeSlices, const std::vector<unsigned int> indices);
        int  loadTexture(unsigned int textureID);
        void render(void);

    protected:
        unsigned int vboID = 0;
        unsigned int vaoID = 0;
        unsigned int eboID = 0;

        std::vector<unsigned int> textureIDs;

        unsigned int numOfPoints = 0;

        void initBuffers(void);
        void loadVertices(const std::vector<float> vertices);
        unsigned int loadAttributes(const std::vector<float> attributeSlices);
        void loadIndices(const std::vector<unsigned int> indices);
};
