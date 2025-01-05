#include "ManualCamera.hpp"

void ManualCamera::setPosition(glm::vec3 position)
{
    cameraProperties.position = position;
}

void ManualCamera::setTarget(glm::vec3 target)
{
    cameraProperties.target = target;
}

void ManualCamera::setUpVector(glm::vec3 upVector)
{
    cameraProperties.upVector = upVector;
}

void ManualCamera::updateView(Shader& shader)
{
    glm::vec3 position = cameraProperties.position;
    glm::vec3 target = cameraProperties.target;
    glm::vec3 upVector = cameraProperties.upVector;

    glm::vec3 forwardAxis = glm::normalize(position - target);
    glm::vec3 rightAxis = glm::normalize(glm::cross(upVector, forwardAxis));
    glm::vec3 upAxis = glm::cross(forwardAxis, rightAxis);

    glm::mat4 cameraMat = glm::mat4(
        glm::vec4(rightAxis, 0.0f),
        glm::vec4(upAxis, 0.0f),
        glm::vec4(forwardAxis, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    cameraMat = glm::transpose(cameraMat);
    glm::vec3 translateVector = glm::vec3(-position[0], -position[1], -position[2]);
    glm::mat4 lookAt = glm::translate(cameraMat, translateVector);
    shader.setMat4("view", lookAt);
}
