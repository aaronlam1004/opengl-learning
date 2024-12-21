#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

typedef float vec4[4];
typedef float vec3[3];

class Shader
{
    public:
        Shader() {};
        Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
        void load(const char* vertexShaderFile, const char* fragmentShaderFile);
        void use();

        void setInt(const char* varName, int value);
        void setVec4(const char* varName, vec4 vec);

    private:
        void loadVertexShader(const char* vertexShaderFile);
        void loadFragmentShader(const char* fragmentShaderFile);
        void compile();
        void compileVertexShader();
        void compileFragmentShader();
        int findVar(const char* varName);
    
    private:
        unsigned int id = glCreateProgram();
        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        std::string vertexShader = "";
        std::string fragmentShader = "";
};
