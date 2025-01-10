#pragma once

struct CameraProperties
{
    // Location
    glm::vec3 position; // Camera position
    glm::vec3 target;   // Target positiion
    glm::vec3 up;       // Orientation of "up" direction of camera

    // Front
    glm::vec3 front; // Front of camera position

    // Angle
    float yaw   = -90.0f; // Yaw
    float pitch =   0.0f; // Pitch
    float fov   =  45.0f; // Field of view
};
