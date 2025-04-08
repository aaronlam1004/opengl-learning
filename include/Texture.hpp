#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include <Logger.hpp>

class Texture
{
    public:
        Texture();
        int load(const char* textureFile, bool hasAlpha, bool flipped, const char* textureUniform);
        int getID(void);

        void setUniform(const char* textureUniform);
        const char* getUniform(void);

    private:
        unsigned int textureID = 0;
        const char* uniform = "";
};
