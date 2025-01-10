#include "Camera.hpp"

Camera::Camera(glm::vec3 position)
{
    cameraProperties.up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraProperties.front = glm::vec3(0.0f, 0.0f, -3.0f);
    cameraProperties.position = position;
    cameraProperties.target = cameraProperties.position + cameraProperties.front;
}

void Camera::setPosition(glm::vec3 position)
{
    cameraProperties.position = position;
}

void Camera::setTarget(glm::vec3 target)
{
    cameraProperties.target = target;
}

void Camera::setUpVector(glm::vec3 up)
{
    cameraProperties.up = up;
}

void Camera::setFront(glm::vec3 front)
{
    cameraProperties.front = front;
}

void Camera::updatePosition(float delta, char axis)
{
    switch (axis)
    {
        case 'x':
        {
            glm::vec3 front = cameraProperties.front;
            glm::vec3 up = cameraProperties.up;
            glm::vec3 rightAxis = glm::normalize(glm::cross(front, up));
            cameraProperties.position += rightAxis * delta;
        } break;
        case 'y':
        {
            glm::vec3 front = cameraProperties.front;
            glm::vec3 up = cameraProperties.up;
            glm::vec3 rightAxis = glm::normalize(glm::cross(front, up));
            glm::vec3 upAxis = glm::normalize(glm::cross(front, rightAxis));
            cameraProperties.position += upAxis * delta;
        } break;
        case 'z':
        {
            cameraProperties.position += cameraProperties.front * delta;
        } break;
        default: break;
    }
}

void Camera::updateAngle(float deltaX, float deltaY)
{
    float pitch = cameraProperties.pitch;
    pitch += deltaY;
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    cameraProperties.pitch = pitch;
    
    cameraProperties.yaw += deltaX;
    float yaw = cameraProperties.yaw;

    glm::vec3 direction = glm::vec3(1.0f);
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraProperties.front = glm::normalize(direction);
}

void Camera::updateZoom(float deltaZ)
{
    float fov = cameraProperties.fov;
    fov -= deltaZ;
    if (fov < 1.0f)
    {
        fov = 1.0f;
    }
    else if (fov > 45.0f)
    {
        fov = 45.0f;
    }
    cameraProperties.fov = fov;
}

glm::mat4 Camera::getLookAt(glm::vec3 position, glm::vec3 target)
{
    glm::mat4 lookAt = glm::mat4(1.0f);
#ifdef MANUAL
    glm::vec3 position = position;
    glm::vec3 target = target;
    glm::vec3 up = cameraProperties.up;

    glm::vec3 forwardAxis = glm::normalize(position - target);
    glm::vec3 rightAxis = glm::normalize(glm::cross(up, forwardAxis));
    glm::vec3 upAxis = glm::cross(forwardAxis, rightAxis);

    glm::mat4 cameraMat = glm::mat4(
        glm::vec4(rightAxis, 0.0f),
        glm::vec4(upAxis, 0.0f),
        glm::vec4(forwardAxis, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    cameraMat = glm::transpose(cameraMat);
    glm::vec3 translateVector = glm::vec3(-position[0], -position[1], -position[2]);
    lookAt = glm::translate(cameraMat, translateVector);
#else
    lookAt = glm::lookAt(position,
                         target,
                         cameraProperties.up);
#endif
    return lookAt;
}

void Camera::setTempView(Shader& shader, glm::vec3 position, glm::vec3 target)
{
    glm::mat4 lookAt = getLookAt(position, target);
    shader.setMat4("view", lookAt);
}

void Camera::setTempPerspective(Shader& shader, float fov, float width, float height)
{
    glm::mat4 projection = glm::perspective(fov, width / height, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
}

void Camera::setCamera(Shader& shader, float width, float height)
{
    cameraProperties.target = cameraProperties.position + cameraProperties.front;
    glm::mat4 lookAt = getLookAt(cameraProperties.position, cameraProperties.target);
    shader.setMat4("view", lookAt);

    glm::mat4 projection = glm::perspective(glm::radians(cameraProperties.fov), width / height, 0.1f, 100.0f);
    shader.setMat4("projection", projection);
}
