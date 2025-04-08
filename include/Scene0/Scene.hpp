#pragma once

#include <cassert>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Scene.hpp>
#include <Entity.hpp>
#include <Mesh.hpp>
#include <Logger.hpp>
#include <Camera.hpp>

#include <Shaders.hpp>
#include <Meshes.hpp>
#include <Textures.hpp>

extern const float WIDTH;
extern const float HEIGHT;

extern Camera camera;
extern bool freeCamera;

enum CameraType
{
    NONE = 0,
    FREE,
    DEMO
};

struct EntityData_Scene0
{
    Shader* shader;
    Mesh* mesh;
    std::vector<Texture*> textures;
    void (*update)(Entity* self) = nullptr;
    bool is3D = false;
    int count = 1;
    int cameraType = CameraType::NONE;
};

void updateGreenColor(Entity* self)
{
    float timeVal = glfwGetTime();
    float green = (sin(5 * timeVal) * 0.35) + 0.65;
    glm::vec4 color = glm::vec4(0.0, green, 0.0, 1.0);
    self->shader->setVec4f("ourColor", color);
}

void rotateContainer(Entity* self)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float) glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    self->shader->setMat4f("transform", transform);
}

void updatePerspective(Entity* self)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);

    self->shader->setMat4f("model", model);
    self->shader->setMat4f("view", view);
    self->shader->setMat4f("projection", projection);
}

void updateCubeRotation(Entity* self)
{
    updatePerspective(self);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float) glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    self->shader->setMat4f("model", model);
}

const glm::vec3 CUBE_POSITIONS[] = {
    glm::vec3( 0.0f, 0.0f, 0.0f),
    glm::vec3( 2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f, 2.0f, -2.5f),
    glm::vec3( 1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

std::vector<EntityData_Scene0> ENTITIES_SCENE0_DATA = {
    { &HELLO_TRIANGLE_SHADER, &TRIANGLE_MESH },
    { &HELLO_TRIANGLE_SHADER, &SQUARE_MESH },
    { &RED_TRIANGLE_SHADER, &TRIANGLE_MESH },
    { &UNIFORM_SHADER, &TRIANGLE_MESH, {}, updateGreenColor },
    { &INTERPOLATION_SHADER, &COLORED_TRIANGLE_MESH },
    { &TEXTURE_SHADER, &COLORED_CONTAINER_MESH, { &CONTAINER_TEXTURE } },
    { &COLOR_MASK_TEXTURE_SHADER, &COLORED_CONTAINER_MESH, { &CONTAINER_TEXTURE } },
    { &TEXTURES_COMBINED_SHADER, &COLORED_CONTAINER_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE } },
    { &TRANSFORMATIONS_SHADER, &TEXTURED_CONTAINER_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE }, rotateContainer },
    { &COORDINATE_SYSTEM_SHADER, &TEXTURED_CONTAINER_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE }, updatePerspective, true },
    { &COORDINATE_SYSTEM_SHADER, &TEXTURED_CUBE_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE }, updateCubeRotation, true },
    { &COORDINATE_SYSTEM_SHADER, &TEXTURED_CUBE_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE }, updatePerspective, true, 6 },
    { &COORDINATE_SYSTEM_SHADER, &TEXTURED_CUBE_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE }, updatePerspective, true, 6, CameraType::DEMO },
    { &COORDINATE_SYSTEM_SHADER, &TEXTURED_CUBE_MESH, { &CONTAINER_TEXTURE, &FACE_TEXTURE }, updatePerspective, true, 6, CameraType::FREE },
};

std::vector<Entity> ENTITIES_SCENE0(ENTITIES_SCENE0_DATA.size());

void setupEntities_Scene0(void)
{
    loadShaders_Scene0();
    loadMeshes_Scene0();
    loadTextures_Scene0();
    for (int i = 0; i < ENTITIES_SCENE0_DATA.size(); ++i)
    {
        EntityData_Scene0 entityData = ENTITIES_SCENE0_DATA[i];
        ENTITIES_SCENE0[i].shader = entityData.shader;
        ENTITIES_SCENE0[i].mesh = entityData.mesh;
        for (int j = 0; j < entityData.textures.size(); ++j)
        {
            ENTITIES_SCENE0[i].loadTexture(entityData.textures[j]);
        }
        ENTITIES_SCENE0[i].updateEntity = entityData.update;
        assert(ENTITIES_SCENE0[i].isLoaded());
    }
}

void renderEntity_Scene0(int index)
{
    EntityData_Scene0 entityData = ENTITIES_SCENE0_DATA[index];
    Entity entity = ENTITIES_SCENE0[index];
    if (entityData.is3D)
    {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    for (int i = 0; i < entityData.count; ++i)
    {
        if (entityData.count > 1)
        {
            glm::vec3 position = CUBE_POSITIONS[i];
            glm::mat4 model = glm::mat4(1.0f);
            float angle = 20.0f * i;
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 3.0f, 0.5f));
            entity.shader->setMat4f("model", model);
        }
        
        if (entityData.cameraType == CameraType::DEMO)
        {
            freeCamera = false;
            const float radius = 10;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            camera.view(entity, 45.0f, glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else if (entityData.cameraType == CameraType::FREE)
        {
            freeCamera = true;
            camera.view(entity);
        }
        else
        {
            freeCamera = false;
        }
        
        entity.render();
        entity.update();
    }
}


Scene SCENE_0 = {
    0,
    setupEntities_Scene0,
    renderEntity_Scene0,
    ENTITIES_SCENE0.size(),
    glm::vec4(0.2f, 0.3f, 0.3f, 1.0f)
};
