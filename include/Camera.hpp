#pragma once

#include "Shader.hpp"
#include "CameraProperties.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
    
class Camera
{
	public:
        Camera(glm::vec3 position);
        void setPosition(glm::vec3 position);
        void setTarget(glm::vec3 target);
        void setUpVector(glm::vec3 up);
        void setFront(glm::vec3 front);

        void updatePosition(float delta, char axis);
        void updateFront(float delta);
    
        void setTempView(glm::vec3 position, glm::vec3 target, Shader& shader);
        void setCamera(Shader& shader);

    protected:
        glm::mat4 getLookAt(glm::vec3 position, glm::vec3 target);
    
    private:
        CameraProperties cameraProperties;
};
