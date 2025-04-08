#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Entity.hpp>

class Camera
{
    public:
        Camera(float sceneWidth, float sceneHeight);
        void setUp(glm::vec3 cameraUp);
        void setPosition(glm::vec3 cameraPosition);
        void setTarget(glm::vec3 cameraTarget);
        void setFront(glm::vec3 cameraFront);
        glm::mat4 getLookAt(glm::vec3 position, glm::vec3 target);

        glm::vec3 getPosition(void);

        void view(const Entity& entity);
        void view(const Entity& entity, float cameraFov, glm::vec3 cameraPosition, glm::vec3 cameraTarget);

        void updateViewAngle(float deltaX, float deltaY);
        void updateZoom(float deltaZ);
        void updateViewPosition(glm::vec3 deltas);

    private:
        float width;
        float height;
    
        // Location
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Orientation of "up" direction of camera
        glm::vec3 position = glm::vec3(0.0f);       // Camera position
        glm::vec3 target = position + front;        // Target position

        // Front
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -3.0f);

        float yaw = -90.0f; // Yaw
        float pitch = 0.0f; // Pitch
        float fov = 45.0f;  // Field of view
};
