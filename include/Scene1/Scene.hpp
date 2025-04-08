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

Color LIGHT_COLOR { 1.0f, 1.0f, 1.0f };
Color OBJ_COLOR   { 1.0f, 0.5f, 0.31f };

Pos LIGHT_POS { 0.0f, 2.0f, 0.0f };
Pos OBJ_POS   { 0.0f, 0.0f, 0.0f };

struct EntityData_Scene1
{
    Shader* shader;
    Mesh* mesh;
    float scale = 1.0f;
    Pos position { 0.0f, 0.0f, 0.0f };
    Color color { 1.0f, 1.0f, 1.0f };
    bool isLighted = false;
    // std::vector<Texture*> textures;
    // void (*update)(Entity* self) = nullptr;
};

std::vector<std::vector<EntityData_Scene1>> ENTITIES_SCENE1_DATA = {
    {
        { &LIGHT_SHADER, &CUBE_MESH, 0.2f, LIGHT_POS },
        { &LIGHTED_CUBE_SHADER, &LIGHTED_CUBE_MESH, 1.0f, OBJ_POS, OBJ_COLOR, true }
    }
};

std::vector<std::vector<Entity>> ENTITIES_SCENE1(ENTITIES_SCENE1_DATA.size());

void setupEntities_Scene1(void)
{
    loadShaders_Scene1();
    loadMeshes_Scene1();
    for (int i = 0; i < ENTITIES_SCENE1_DATA.size(); ++i)
    {
        std::vector<EntityData_Scene1> entitiesData = ENTITIES_SCENE1_DATA[i];
        std::vector<Entity>& entities = ENTITIES_SCENE1[i];
        for (int j = 0; j < entitiesData.size(); ++j)
        {
            EntityData_Scene1 entityData = entitiesData[j];

            Entity entity;
            entity.shader = entityData.shader;
            entity.mesh = entityData.mesh;

            entity.pos = entityData.position;
            entity.color = entityData.color;

            assert(entity.isLoaded());

            if (entityData.isLighted)
            {
                entity.shader->setVec3f("objectColor", glm::vec3(entity.color.r, entity.color.g, entity.color.b));
                entity.shader->setVec3f("lightColor", glm::vec3(LIGHT_COLOR.r, LIGHT_COLOR.g, LIGHT_COLOR.b));
                entity.shader->setVec3f("lightPos", glm::vec3(LIGHT_POS.x, LIGHT_POS.y, LIGHT_POS.z));
            }
            
            /*
            for (int k = 0; k < entityData.textures.size(); ++k)
            {
                entity.loadTexture(entityData.textures[k]);
            }
            entity.updateEntity = entityData.update;
            */
            
            entities.push_back(entity);
        }
    }
}

void renderEntity_Scene1(int index)
{
    freeCamera = true;
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < ENTITIES_SCENE1[index].size(); ++i)
    {
        EntityData_Scene1 entityData = ENTITIES_SCENE1_DATA[index][i];
        Entity entity = ENTITIES_SCENE1[index][i];

        if (entityData.isLighted)
        {
            entity.shader->setVec3f("viewPos", camera.getPosition());
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(entity.pos.x, entity.pos.y, entity.pos.z));
        model = glm::scale(model, glm::vec3(entityData.scale));
        entity.shader->setMat4f("model", model);
        
        camera.view(entity);

        entity.render();
        entity.update();
    }
}


Scene SCENE_1 = {
    1,
    setupEntities_Scene1,
    renderEntity_Scene1,
    ENTITIES_SCENE1_DATA.size(),
    glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)
};
