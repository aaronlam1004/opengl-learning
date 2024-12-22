#pragma once

#include "stb_image.h"
#include <glad/glad.h>

class Texture
{
    public:
        Texture();
        Texture(const char* textureFile);
        void load(const char* textureFile,
                  bool hasAlpha = false,
                  bool flipImage = false);
        void use(unsigned int textureLocation = GL_TEXTURE0);
    
    private:
        bool loaded = false;
        unsigned int id;
        int width = 0;
        int height = 0;
        int numChannels = 0;
        unsigned char* data = nullptr; 
};
