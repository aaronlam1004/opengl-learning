#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef float vec4[4];
typedef float vec3[3];

struct Shader {
    // Shader source
    std::string vertexShader = "";
    std::string fragmentShader = "";

    // Shader IDs
    unsigned int shaderID = glCreateProgram();
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    //
    //  Load vertex and fragment shaders
    //
    //  @param[in] vertexShaderFile
    //  @param[in] fragmentShaderFile
    //
    void load(const char* vertexShaderFile, const char* fragmentShaderFile)
    {
        loadVertexShader(vertexShaderFile);
        loadFragmentShader(fragmentShaderFile);
    }

    //
    //  Compiles the vertex and fragment shaders and attaches
    //  them so that they can be used
    //
    void compile()
    {
        // Compile the shaders
        compileVertexShader();
        compileFragmentShader();

        // Create the shader program
        glAttachShader(shaderID, vertexShaderID);
        glAttachShader(shaderID, fragmentShaderID);
        glLinkProgram(shaderID);

        // Clean up since attached
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    //
    //
    //
    int findVar(const char* var)
    {
        return glGetUniformLocation(shaderID, var);
    }

    //
    //
    //
    void setVec4(const char* var, float vec4[4])
    {
        glUniform4f(findVar(var), vec4[0], vec4[1], vec4[2], vec4[3]);
    }

    //
    //  Use the shader
    //
    void use()
    {
        glUseProgram(shaderID);
    }

    //
    // Load vertex shader from source
    //
    // @param[in] vertexShaderSource
    //
    void loadVertexShader(const char* vertexShaderFile)
    {
        std::ifstream vertexShaderSource(vertexShaderFile);
        std::stringstream vertexShaderStream;
        vertexShaderStream << vertexShaderSource.rdbuf();
        vertexShaderSource.close();
        vertexShader = vertexShaderStream.str();
    }

    //
    // Compiles the vertex shader
    //
    void compileVertexShader()
    {
        const char* vertShader = vertexShader.c_str();
        glShaderSource(vertexShaderID, 1, &vertShader, NULL);
        glCompileShader(vertexShaderID);
    }

    //
    // Load fragment shader from source
    //
    // @param[in] fragmentShaderSource
    //
    void loadFragmentShader(const char* fragmentShaderFile)
    {
        std::ifstream fragmentShaderSource(fragmentShaderFile);
        std::stringstream fragmentShaderStream;
        fragmentShaderStream << fragmentShaderSource.rdbuf();
        fragmentShaderSource.close();
        fragmentShader = fragmentShaderStream.str();
    }

    //
    // Compiles the fragment shader
    //
    void compileFragmentShader()
    {
        const char* fragShader = fragmentShader.c_str();
        glShaderSource(fragmentShaderID, 1, &fragShader, NULL);
        glCompileShader(fragmentShaderID);
    }
};
