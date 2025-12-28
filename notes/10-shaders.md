# Chapter 10: Shaders (Beginner Friendly)

This chapter introduces **shaders** in OpenGL. Shaders are **small programs** that run on the GPU to control how your graphics are drawn.  
They allow you to change how vertices and pixels appear on the screen.

---

## What Are Shaders?

In OpenGL, you don’t just tell the GPU “draw this triangle.” You give it **programs** that describe:

1. How to **process each vertex** (position, color, etc.)
2. How to **compute the color of each pixel** (lighting, textures, effects)

There are two main types of shaders in basic OpenGL:

- **Vertex Shader**  
  Processes each vertex. It transforms vertex positions and can pass data to the next stage.
- **Fragment Shader**  
  Processes each pixel (fragment). It decides the final color that appears on the screen.

Think of it as a **factory line**:

- Vertex Shader = shapes parts
- Fragment Shader = paints them

---

## Key Concepts for Beginners

1. **GLSL** – The programming language for OpenGL shaders. It’s like C but specialized for graphics.
2. **Shader Program** – You combine your vertex and fragment shaders into a program. The GPU runs this program to render objects.
3. **Attributes** – Input data to the vertex shader (position, color, etc.).
4. **Uniforms** – Global variables sent from the CPU to the shader (like color, transformation matrices, etc.).
5. **Varyings** – Data passed from the vertex shader to the fragment shader (like color, texture coordinates).

---

## Steps to Use Shaders

1. **Write a Vertex Shader** (`vertex_shader.glsl`)
2. **Write a Fragment Shader** (`fragment_shader.glsl`)
3. **Load and Compile Shaders** in your OpenGL program
4. **Link them into a Shader Program**
5. **Use the Shader Program** when rendering

---

## Example Code: Basic Shaders in OpenGL

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec2 aPos;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // orange color
}
)";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders Example", nullptr, nullptr);
    if (!window) { std::cout << "Failed to create GLFW window\n"; glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cout << "Failed to initialize GLAD\n"; return -1; }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Compile Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Compile Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Link Shaders into Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Triangle vertices
    float vertices[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
```
