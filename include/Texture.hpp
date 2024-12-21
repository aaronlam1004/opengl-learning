#pragma once

#include "stb_image.h"
#include <glad/glad.h>

class Texture
{
    public:
        Texture();
        Texture(const char* textureFile);
        void load(const char* textureFile);
        void use();
    
    private:
        bool loaded = false;
        unsigned int id;
        int width = 0;
        int height = 0;
        int numChannels = 0;
        unsigned char* data = nullptr; 
};
