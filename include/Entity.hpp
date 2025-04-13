#pragma once

#include <cassert>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Logger.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

struct Size
{
    float width;
    float height;
};

struct Position
{
    float x;
    float y;
    float z;
};

struct Velocity
{
    float x;
    float y;
};

struct Color
{
    float r;
    float g;
    float b;

    glm::vec3 toVec(void)
    {
        return glm::vec3(r, g, b);
    }
};

struct Material
{
    glm::vec3 ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
    float shininess = 32.0f;
};

struct Lighting
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct Entity
{
    int type     { -1 };
    Size size    { 0.0f, 0.0f };
    Position pos { 0.0f, 0.0f, 0.0f };
    Velocity vel { 0.0f, 0.0f };
    Color color  { 1.0f, 1.0f, 1.0f };
    float scale  { 1.0f };

    // TODO: add Material parameter
    
    Shader* shader = nullptr;
    Mesh*   mesh   = nullptr;

    void (*updateEntity)(Entity* self) = nullptr;
    void (*renderEntity)(Entity* self) = nullptr;

    virtual bool isLoaded(void)
    {
        return (shader != nullptr) && (mesh != nullptr);
    }

    virtual void loadTexture(Texture* texture)
    {
        int textureIndex = mesh->loadTexture(texture->getID());
        if (texture->getUniform() != "" && textureIndex != -1)
        {
            assert(shader != nullptr);
            shader->setInt(texture->getUniform(), textureIndex);
        }
    }

    virtual void render(void)
    {
        assert(shader != nullptr);
        assert(mesh != nullptr);
        if (renderEntity != nullptr)
        {
            renderEntity(this);
        }
        else
        {
            shader->use();
            mesh->render();
        }
    }

    virtual void update(void)
    {
        if (updateEntity != nullptr)
        {
            updateEntity(this);
        }
    }
};
