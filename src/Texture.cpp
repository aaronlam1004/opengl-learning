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

Texture::Texture(const char* textureFile, bool hasAlpha, bool flipImage) :
    Texture()
{
    load(textureFile, hasAlpha, flipImage);
}

//
//  Load the texture
//
//  @param[in] textureFile
//
void Texture::load(const char* textureFile, bool hasAlpha, bool flipImage)
{
    stbi_set_flip_vertically_on_load(flipImage);
    data = stbi_load(textureFile, &width, &height, &numChannels, 0);
    if (data)
    {
        unsigned int format = hasAlpha ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    loaded = true;
}

void Texture::use(unsigned int textureLocation)
{
    if (loaded)
    {
        glActiveTexture(textureLocation);
        glBindTexture(GL_TEXTURE_2D, id);
    }
}


