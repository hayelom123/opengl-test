#include "config.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window);

std::string loadShaderSourceFromFile(const std::string &filepath);

static int shaderCompileStatus(GLuint shader)
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

static int programLinkStatus(GLuint program)
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
static int createShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);

int main()
{
    // intialize
    glfwInit();

    // set window config to 3.3

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 //.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core the latest specification

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac devices
#endif

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Opengl Test", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // shaders
    // Read shader sources
    std::string vertexCode = loadShaderSourceFromFile(vertexShaderPath);
    std::string fragmentCode = loadShaderSourceFromFile(fragmentShaderPath);

    if (vertexCode.empty() || fragmentCode.empty())
    {
        std::cerr << "Failed to load shader files!" << std::endl;
        return -1;
    }
    const char *vertexShaderSource = vertexCode.c_str();
    const char *fragmentShaderSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // link shaders
    GLuint program = createShader(vertexShaderSource, fragmentShaderSource);

    // draw traingle
    float postions[] = {
        -0.5f, -0.5f, // bottom left
        0.0f, 0.5f,   // top
        0.5f, -0.5f   // bottom right

    };

    // load data to buffer
    GLuint VBO, VAO;
    // 1
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 1 Bind VAO first
    glBindVertexArray(VAO);

    // 2. Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(postions), postions, GL_STATIC_DRAW);

    // 3. Describe vertex layout
    glVertexAttribPointer(
        0,                 // location or index
        2,                 // how many points for one vertices
        GL_FLOAT,          // data type
        GL_FALSE,          // normalized
        2 * sizeof(float), // stripe the size of one point
        (void *)0);

    // 4. Enable attribute
    glEnableVertexAttribArray(0);

    // 5. Unbind VAO(optional)
    // glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        // window background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        // target,starting, how many vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional phase delete everything

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);

    glfwDestroyWindow(window);

    glfwTerminate();
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
static int createShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
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