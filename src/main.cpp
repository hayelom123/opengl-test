#include "config.h"
#include "utils.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    std::cout << "HELLO GOD!!!" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
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
        glfwTerminate();
        return -1;
    }

    // load shaders
    std::string vertexShaderPath = "../shaders/triangles/triangle.vert";
    std::string fragmentShaderPath = "../shaders/triangles/triangle.frag";

    std::string vertexCode = loadShaderSourceFromFile(vertexShaderPath);
    std::string fragmentCode = loadShaderSourceFromFile(fragmentShaderPath);

    unsigned int shaderProgram = createShader(
        vertexCode,
        fragmentCode);

    float positions[] = {
        0.3f,
        0.5f, // 0

        -0.3f,
        -0.5f, // 1

        -0.3f,
        0.3f, // 2
        // first triangle

        -0.5f,
        0.3f, // 3
        -0.5f,
        -0.3f, // 4
        -0.3f,
        -0.3f, // 5
        -0.3f,
        -0.8f, // 6
        0.3f,
        -0.8f, // 7
        0.3f,
        -0.3f, // 8
        0.5f,
        -0.3f, // 9
        0.5f,
        0.3f, // 10
        0.3f,
        0.3f, // 11

    };
    unsigned int indices[] = {
        // Top vertical rectangle
        0, 2, 11,
        11, 10, 0,

        // Center vertical rectangle
        2, 5, 8,
        8, 11, 2,

        // Bottom vertical rectangle
        5, 6, 7,
        7, 8, 5,

        // Left horizontal rectangle
        3, 2, 5,
        5, 4, 3,

        // Right horizontal rectangle
        11, 8, 9,
        9, 10, 11};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}