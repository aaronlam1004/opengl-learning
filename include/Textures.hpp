#pragma once

#include <Texture.hpp>

Texture CONTAINER_TEXTURE;
Texture FACE_TEXTURE;

void loadTextures_Scene0(void)
{
    CONTAINER_TEXTURE.load("resources/textures/container.jpg", false, false, "containerTexture");
    FACE_TEXTURE.load("resources/textures/awesomeface.png", true, true, "faceTexture");
}
