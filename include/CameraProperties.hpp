#pragma once

struct CameraProperties
{
    // Location
    glm::vec3 position; // Camera position
    glm::vec3 target;   // Target positiion
    glm::vec3 up;       // Orientation of "up" direction of camera

    // View
    glm::vec3 front;    // Front of camera position
    float yaw;          // Yaw
    float pitch;        // Pitch
    float fov;          // Field of view
};
