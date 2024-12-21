#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"

Texture::Texture()
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const char* textureFile) :
    Texture()
{
    load(textureFile);
}

//
//  Load the texture
//
//  @param[in] textureFile
//
void Texture::load(const char* textureFile)
{
    data = stbi_load(textureFile, &width, &height, &numChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
}

void Texture::use()
{
    // glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, id);
}


