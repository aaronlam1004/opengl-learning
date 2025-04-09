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
#include <Materials.hpp>

Color LIGHT_COLOR { 1.0f, 1.0f, 1.0f };
Color OBJ_COLOR   { 0.0f, 1.0f, 0.0f };

Pos LIGHT_POS { 1.2f, 1.0f, 2.0f };
Pos OBJ_POS   { 0.0f, 0.0f, 0.0f };

struct EntityData_Scene1
{
    bool isLight;
    Shader* shader;
    Mesh* mesh;
    float scale = 1.0f;
    Pos position { 0.0f, 0.0f, 0.0f };
    Color color { 1.0f, 1.0f, 1.0f };
    void (*update)(Entity* self) = nullptr;
    Material material = DEFAULT_MATERIAL;
    Lighting lighting = {
        glm::vec3(0.2f),
        glm::vec3(0.5f),
        glm::vec3(1.0f)
    };
    // std::vector<Texture*> textures;
};

void translateAndScaleModel(Entity* self)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(self->pos.x, self->pos.y, self->pos.z));
    model = glm::scale(model, glm::vec3(self->scale));
    self->shader->setMat4f("model", model);
}

void orbitCubeLatitude(Entity* self)
{
    translateAndScaleModel(self);
    /*
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(self->pos.x, self->pos.y, self->pos.z));
    model = glm::rotate(model, (float) glfwGetTime() * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(self->scale));
    self->shader->setMat4f("model", model);
    */
}

void updateLightColor(Entity* self)
{
    translateAndScaleModel(self);
    self->color.r = sin(glfwGetTime() * 2.0f);
    self->color.g = sin(glfwGetTime() * 0.7f);
    self->color.b = sin(glfwGetTime() * 1.3f);
}

std::vector<std::vector<EntityData_Scene1>> ENTITIES_SCENE1_DATA = {
    {
        { true, &LIGHT_SHADER, &CUBE_MESH, 0.2f, LIGHT_POS, LIGHT_COLOR, translateAndScaleModel },
        { false, &LIGHTED_CUBE_SHADER, &LIGHTED_CUBE_MESH, 1.0f, OBJ_POS, OBJ_COLOR, translateAndScaleModel }
    },
    {
        { true, &LIGHT_SHADER, &CUBE_MESH, 0.2f, LIGHT_POS, LIGHT_COLOR, translateAndScaleModel },
        { false, &MATERIAL_CUBE_SHADER, &LIGHTED_CUBE_MESH, 1.0f, OBJ_POS, OBJ_COLOR, translateAndScaleModel }
    },
    {
        { true, &LIGHT_SHADER, &CUBE_MESH, 0.2f, LIGHT_POS, LIGHT_COLOR, orbitCubeLatitude },
        { false, &MATERIAL_CUBE_SHADER, &LIGHTED_CUBE_MESH, 1.0f, OBJ_POS, OBJ_COLOR, translateAndScaleModel }
    },
    {
        { true, &COLORED_LIGHT_SHADER, &CUBE_MESH, 0.2f, LIGHT_POS, LIGHT_COLOR, updateLightColor },
        { false, &MATERIAL_CUBE_SHADER, &LIGHTED_CUBE_MESH, 1.0f, OBJ_POS, OBJ_COLOR, translateAndScaleModel }
    },
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
            EntityData_Scene1& entityData = entitiesData[j];

            Entity entity;
            entity.shader = entityData.shader;
            entity.mesh = entityData.mesh;

            entity.pos = entityData.position;
            entity.color = entityData.color;
            entity.scale = entityData.scale;
            // entity.material = entityData.material;

            assert(entity.isLoaded());

            if (!entityData.isLight)
            {
                // Object Color
                entity.shader->setVec3f("objectColor", glm::vec3(entity.color.r, entity.color.g, entity.color.b));

                // Material
                entity.shader->setVec3f("material.ambient", entityData.material.ambient);
                entity.shader->setVec3f("material.diffuse", entityData.material.diffuse);
                entity.shader->setVec3f("material.specular", entityData.material.specular);
                entity.shader->setFloat("material.shininess", entityData.material.shininess);

                // Light
                entity.shader->setVec3f("light.specular", entityData.lighting.specular);
            }
            
            /*
            for (int k = 0; k < entityData.textures.size(); ++k)
            {
                entity.loadTexture(entityData.textures[k]);
            }
            */
            entity.updateEntity = entityData.update;            
            entities.push_back(entity);
        }
    }
}

void renderEntity_Scene1(int index)
{
    freeCamera = true;
    
    glm::vec3 lightPos = glm::vec3(0.0f);
    glm::vec3 lightColor = glm::vec3(0.0f);
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < ENTITIES_SCENE1[index].size(); ++i)
    {
        EntityData_Scene1 entityData = ENTITIES_SCENE1_DATA[index][i];
        Entity& entity = ENTITIES_SCENE1[index][i];

        if (entityData.isLight)
        {
            lightPos = glm::vec3(entity.pos.x, entity.pos.y, entity.pos.z);
            lightColor = glm::vec3(entity.color.r, entity.color.g, entity.color.b);
        }
        else
        {
            glm::vec3 diffuseColor = lightColor * entityData.lighting.ambient;
            glm::vec3 ambientColor = diffuseColor * entityData.lighting.diffuse;
            entity.shader->setVec3f("light.ambient", ambientColor);
            entity.shader->setVec3f("light.diffuse", diffuseColor);
            entity.shader->setVec3f("viewPos", camera.getPosition());
        }

        entity.shader->setVec3f("lightPos", lightPos);
        entity.shader->setVec3f("lightColor", lightColor);

        
        
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
