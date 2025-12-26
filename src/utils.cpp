
#include "utils.h"

int shaderCompileStatus(GLuint shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    return success;
}

int programLinkStatus(GLuint program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    return success;
}
static unsigned int compileShader(unsigned int shaderType, const std::string &source)
{
    GLuint shader = glCreateShader(shaderType);

    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    if (!shaderCompileStatus(shader))
    {
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
int createShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    // link shaders
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    // glValidateProgram(program); //only for debug
    // check link status
    if (!programLinkStatus(program))
    {
        glDeleteProgram(program);
        program = 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

std::string loadShaderSourceFromFile(const std::string &filepath)

{
    std::ifstream file;
    std::stringstream fileStream;

    // Ensure ifstream throws exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(filepath);
        fileStream << file.rdbuf();
        file.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return fileStream.str();
}
