#include "config.h"
#include "stb_image.h"

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

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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

    // load texture data
    int width, height, nrChannels;
    unsigned char *data = stbi_load("./textures/wall.jpg", &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // wraping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method). s axis means x axis of texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method). t axis means y axis of texture

    // filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // when texture is scaled down
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // when texture is scaled up

    // load texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "checkerTex"), 0); // set the texture unit 0 to the sampler2D uniform
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        // rendering commands here

        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        // update the uniform color
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}