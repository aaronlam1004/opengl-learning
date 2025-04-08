#include <Shader.hpp>

Shader::Shader()
{
}

void Shader::use(void)
{
    if (id != -1)
    {
        glUseProgram(id);
    }
    else
    {
        LOG_WARNING("Shader not loaded\n");
    }
}

void Shader::load(const char* vsFile, const char* fsFile)
{
    id = glCreateProgram();
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    bool compiled = loadVertexShader(vsFile);
    compiled &= loadFragmentShader(fsFile);
    if (compiled)
    {
        glLinkProgram(id);
    }
}

bool Shader::loadVertexShader(const char* vsFile)
{
    std::ifstream vertexSource(vsFile);
    if (!vertexSource.good())
    {
        LOG_ERROR("Vertex shader (%s) does not exist\n", vsFile);
        return false;
    }
    
    std::stringstream vertexShaderStream;
    vertexShaderStream << vertexSource.rdbuf();
    vertexSource.close();
    
    std::string vertexShaderString = vertexShaderStream.str();
    const char* vertexShaderSource = vertexShaderString.c_str();
    
    glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderID);

    bool compiled = checkShaderCompiled(vertexShaderID);
    if (compiled)
    {
        LOG_DEBUG("Vertex shader (%s) compiled successfully\n", vsFile); 
        glAttachShader(id, vertexShaderID);
    }
    else
    {
        LOG_ERROR("Vertex shader (%s) failed to compile\n", vsFile);
    }
    glDeleteShader(vertexShaderID);
    return compiled;
}

bool Shader::loadFragmentShader(const char* fsFile)
{
    std::ifstream fragmentSource(fsFile);
    if (!fragmentSource.good())
    {
        LOG_ERROR("Fragment shader (%s) does not exist\n", fsFile);
        return false;
    }
    
    std::stringstream fragmentShaderStream;
    fragmentShaderStream << fragmentSource.rdbuf();
    fragmentSource.close();
    
    std::string fragmentShaderString = fragmentShaderStream.str();
    const char* fragmentShaderSource = fragmentShaderString.c_str();

    glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderID);

    bool compiled = checkShaderCompiled(fragmentShaderID);
    if (compiled)
    {
        LOG_DEBUG("Fragment shader (%s) compiled successfully\n", fsFile); 
        glAttachShader(id, fragmentShaderID);
    }
    else
    {
        LOG_ERROR("Vertex shader (%s) failed to compile\n", fsFile);
    }
    glDeleteShader(fragmentShaderID);
    return compiled;
}

bool Shader::checkShaderCompiled(int shaderID)
{
    int status;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        char infoLog[512] = {0};
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        LOG_ERROR("Shader compilation error:\n%s", infoLog);
    }
    return status != 0;
}

int Shader::findVar(const char* var)
{
    use();
    int location = glGetUniformLocation(id, var);
    if (location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION)
    {
        LOG_ERROR("Could not find %s in shader (status %d)", var, location);
    }
    return location;
}

void Shader::setInt(const char* var, int value)
{
    glUniform1i(findVar(var), value);
}

void Shader::setVec3f(const char* var, glm::vec3 vec)
{
    glUniform3fv(findVar(var), 1, glm::value_ptr(vec));
}

void Shader::setVec4f(const char* var, glm::vec4 vec)
{
    glUniform4fv(findVar(var), 1, glm::value_ptr(vec));
}

void Shader::setMat4f(const char* var, glm::mat4 mat, bool transpose)
{
    glUniformMatrix4fv(findVar(var), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}
