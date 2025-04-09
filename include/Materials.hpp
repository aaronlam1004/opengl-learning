#pragma once

#include <glm/glm.hpp>

#include <Entity.hpp>

float SHININESS_FACTOR = 128.0f;

Material DEFAULT_MATERIAL = {
    glm::vec3(1.0f, 0.5f, 0.31f),
    glm::vec3(1.0f, 0.5f, 0.31f),
    glm::vec3(0.5f, 0.5f, 0.5f),
    32.0f
};

Material EMERALD_MATERIAL = {
    glm::vec3(0.0215f, 0.1745f, 0.0215f),
    glm::vec3(0.07568f, 0.61424f, 0.07568f),
    glm::vec3(0.633f, 0.727811f, 0.633f),
    SHININESS_FACTOR * 0.6f
};

Material GREEN_PLASTIC_MATERIAL = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.1f, 0.35f, 0.1f),
    glm::vec3(0.45f, 0.55f, 0.45f),
    SHININESS_FACTOR * 0.25f
};

