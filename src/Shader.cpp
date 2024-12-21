#include "Shader.hpp"

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile) :
    Shader()
{
    load(vertexShaderFile, fragmentShaderFile);
}

//
//  Load vertex and fragment shaders
//
//  @param[in] vertexShaderFile
//  @param[in] fragmentShaderFile
//
void Shader::load(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    loadVertexShader(vertexShaderFile);
    loadFragmentShader(fragmentShaderFile);
    compile();
}

//
//  Use the shader
//
void Shader::use()
{
    glUseProgram(id);
}

//
//
//
void Shader::setInt(const char* varName, int value)
{
    glUniform1i(findVar(varName), value);
}

//
//
//
void Shader::setVec4(const char* varName, vec4 vec)
{
    glUniform4f(findVar(varName), vec[0], vec[1], vec[2], vec[3]);
}

//
// Load vertex shader from source
//
// @param[in] vertexShaderSource
//
void Shader::loadVertexShader(const char* vertexShaderFile)
{
    std::ifstream vertexShaderSource(vertexShaderFile);
    std::stringstream vertexShaderStream;
    vertexShaderStream << vertexShaderSource.rdbuf();
    vertexShaderSource.close();
    vertexShader = vertexShaderStream.str();
    std::cout << vertexShader << std::endl;
}

//
// Load fragment shader from source
//
// @param[in] fragmentShaderSource
//
void Shader::loadFragmentShader(const char* fragmentShaderFile)
{
    std::ifstream fragmentShaderSource(fragmentShaderFile);
    std::stringstream fragmentShaderStream;
    fragmentShaderStream << fragmentShaderSource.rdbuf();
    fragmentShaderSource.close();
    fragmentShader = fragmentShaderStream.str();
    std::cout << fragmentShader << std::endl;
}

//
//  Compiles the vertex and fragment shaders and attaches
//  them so that they can be used
//
void Shader::compile()
{
    // Compile the shaders
    compileVertexShader();
    compileFragmentShader();

    // Create the shader program
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    glLinkProgram(id);

    // Clean up since attached
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

//
// Compiles the vertex shader
//
void Shader::compileVertexShader()
{
    const char* vertShader = vertexShader.c_str();
    glShaderSource(vertexShaderID, 1, &vertShader, NULL);
    glCompileShader(vertexShaderID);
}

//
// Compiles the fragment shader
//
void Shader::compileFragmentShader()
{
    const char* fragShader = fragmentShader.c_str();
    glShaderSource(fragmentShaderID, 1, &fragShader, NULL);
    glCompileShader(fragmentShaderID);
}

//
//
//
int Shader::findVar(const char* varName)
{
    return glGetUniformLocation(id, varName);
}
