#define STB_IMAGE_IMPLEMENTATION
#include <Texture.hpp>

Texture::Texture()
{
}

int Texture::load(const char* textureFile, bool hasAlpha, bool flipped, const char* textureUniform)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    stbi_set_flip_vertically_on_load(flipped);
    int width, height, numChannels;
    unsigned char* imageData = stbi_load(textureFile, &width, &height, &numChannels, 0);
    if (imageData)
    {
        LOG_DEBUG("Texture (%s) loaded successfully\n", textureFile);
        unsigned int glColModel = hasAlpha ? GL_RGBA : GL_RGB;
        /*
        if (hasAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        */
        glTexImage2D(GL_TEXTURE_2D, 0, glColModel, width, height, 0, glColModel, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
        uniform = textureUniform;
        return textureID;
    }
    else
    {
        LOG_WARNING("Could not load texture (%s)\n", textureFile);
    }
    stbi_image_free(imageData);
    return -1;
}

int Texture::getID(void)
{
    return textureID;
}

const char* Texture::getUniform(void)
{
    return uniform;
}

void Texture::setUniform(const char* textureUniform)
{
    uniform = textureUniform;
}
