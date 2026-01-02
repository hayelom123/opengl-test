#include "config.h"

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGLShaders", NULL, NULL);

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

    // shader compilation
    std::string vertexShaderPath = "../shaders/texture/triangle.vert";
    std::string fragmentShaderPath = "../shaders/texture/triangle.frag";

    std::string vertextShaderSource = loadShaderSourceFromFile(vertexShaderPath);
    std::string fragmentShaderSource = loadShaderSourceFromFile(fragmentShaderPath);

    int shaderProgram = createShader(vertextShaderSource, fragmentShaderSource);

    if (shaderProgram == 0)
    {
        std::cout << "Failed to create shader program" << std::endl;
        return -1;
    }

    // set up vertex data (and buffer(s)) and configure vertex attributes

    // ---------- VERTEX DATA ----------
    float vertices[] = {
        // positions   /*================*///tex coords
        0.5f, 0.5f, /*================*/1.0f, 1.0f,
        0.5f, -0.5f, /*================*/1.0f, 0.0f,
        -0.5f, -0.5f, /*================*/0.0f, 0.0f,

        -0.5f, -0.5f, /*================*/0.0f, 0.0f,
        -0.5f, 0.5f, /*================*/0.0f, 1.0f,
        0.5f, 0.5f, /*================*/1.0f, 1.0f};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    // stride is 4 floats (2 position, 2 texture coordinates)
    // simply put, it is the space between consecutive vertex attributes
    // the pointer is offset of the first component

    // texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    // ---------- CHECKERBOARD TEXTURE ----------
    const int TEX_SIZE = 64;
    unsigned char checker[TEX_SIZE * TEX_SIZE * 3];

    for (int y = 0; y < TEX_SIZE; y++)
    {
        for (int x = 0; x < TEX_SIZE; x++)
        {
            int checkerValue = ((x / 8) + (y / 8)) % 2;
            unsigned char color = checkerValue ? 255 : 0;

            int index = (y * TEX_SIZE + x) * 3;
            checker[index + 0] = color;
            checker[index + 1] = color;
            checker[index + 2] = color;
        }
    }

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        // rendering commands here
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.5f, greenValue, 1.0f, 1.0f);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}