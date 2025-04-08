#include <Camera.hpp>

Camera::Camera(float sceenWidth, float sceenHeight) :
    width(sceenWidth),
    height(sceenHeight)
{
}

void Camera::setUp(glm::vec3 cameraUp)
{
    up = cameraUp;
}

void Camera::setPosition(glm::vec3 cameraPosition)
{
    position = cameraPosition;
}

void Camera::setTarget(glm::vec3 cameraTarget)
{
    target = cameraTarget;
}

void Camera::setFront(glm::vec3 cameraFront)
{
    front = cameraFront;
}

glm::mat4 Camera::getLookAt(glm::vec3 cameraPosition, glm::vec3 cameraTarget)
{
    /*
    glm::mat4 lookAt = glm::mat4(1.0f);
    return lookAt;
    */
    return glm::lookAt(cameraPosition, cameraTarget, up);
}

glm::vec3 Camera::getPosition(void)
{
    return position;
}

void Camera::view(const Entity& entity)
{
    target = position + front;
    view(entity, fov, position, target);
}

void Camera::view(const Entity& entity, float cameraFov, glm::vec3 cameraPosition, glm::vec3 cameraTarget)
{   
    glm::mat4 projection = glm::perspective(glm::radians(cameraFov), width / height, 0.1f, 100.0f);
    entity.shader->setMat4f("projection", projection);
    
    glm::mat4 view = getLookAt(cameraPosition, cameraTarget);
    entity.shader->setMat4f("view", view);
}

void Camera::updateViewAngle(float deltaX, float deltaY)
{
    pitch += deltaY;
    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
    yaw += deltaX;

    glm::vec3 direction = glm::vec3(1.0f);
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    front = glm::normalize(direction);
}

void Camera::updateZoom(float deltaZ)
{
    fov -= deltaZ;
    if (fov < 1.0f)
    {
        fov = 1.0f;
    }
    else if (fov > 45.0f)
    {
        fov = 45.0f;
    }
}

void Camera::updateViewPosition(glm::vec3 deltas)
{
    float deltaX = deltas.x;
    glm::vec3 rightAxis = glm::normalize(glm::cross(front, up));
    position += rightAxis * deltaX;

    float deltaY = deltas.y;
    glm::vec3 upAxis = glm::normalize(glm::cross(front, rightAxis));
    position += upAxis * deltaY;

    float deltaZ = deltas.z;
    position += front * deltaZ;
}
