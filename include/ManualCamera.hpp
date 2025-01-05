/*
// Manual camera handling
// Camera position
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

// Camera Direction
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);

// Camera Right Axis
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRightAxis = glm::normalize(glm::cross(cameraUp, cameraDirection));

// Camera Up Axis
glm::vec3 cameraUpAxis = glm::cross(cameraDirection, cameraRight);
*/
#pragma once

#include "Shader.hpp"
#include "CameraProperties.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ManualCamera
{
	public:
        ManualCamera() {}
        void setPosition(glm::vec3 position);
        void setTarget(glm::vec3 target);
        void setUpVector(glm::vec3 upVector);
        void updateView(Shader& shader);
    
    private:
        CameraProperties cameraProperties;
};
