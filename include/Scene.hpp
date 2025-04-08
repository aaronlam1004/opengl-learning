#pragma once

#include <Logger.hpp>
#include <Camera.hpp>

struct Scene
{
    int id;
    void (*setup)(void) = nullptr;
    void (*render)(int index) = nullptr;
    unsigned int count = 0;
    glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    bool loaded = false;
};

void setupScene(Scene& scene)
{
    LOG_INFO("Loading Scene %d\n", scene.id);
    glClearColor(scene.backgroundColor[0], scene.backgroundColor[1], scene.backgroundColor[2], scene.backgroundColor[3]);
    if (!scene.loaded)
    {
        if (scene.setup != nullptr)
        {
            scene.setup();
        }
        scene.loaded = true;
    }
}

void renderScene(const Scene& scene, int index)
{
    if (scene.render != nullptr)
    {
        scene.render(index);
    }
}
