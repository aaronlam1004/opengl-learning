#pragma once

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Logger.hpp>

class Shader
{
    public:
        Shader();
        void load(const char* vsFile, const char* fsFile);
        void use(void);

        // Set shader variables
        void setInt(const char* var, int value);
        void setFloat(const char* var, float value);
        void setVec3f(const char* var, glm::vec3 vec);
        void setVec4f(const char* var, glm::vec4 vec);
        void setMat4f(const char* var, glm::mat4 mat, bool transpose = false);

    private:
        int id = -1;
        int vertexShaderID = -1;
        int fragmentShaderID = -1;
    
        bool loadVertexShader(const char* vsFile);
        bool loadFragmentShader(const char* fsFile);
        bool checkShaderCompiled(int shaderID);

        int findVar(const char* var);
};
