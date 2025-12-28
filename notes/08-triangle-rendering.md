# Chapter 8: Triangle Rendering

This chapter demonstrates how to set up a basic OpenGL program to render a triangle.
It includes window creation, OpenGL context initialization, shader compilation,
vertex buffer setup, and the render loop.

---

## Key Steps

1. Initialize GLFW and create a window with an OpenGL context
2. Load OpenGL function pointers using GLAD
3. Define vertex data for a triangle
4. Create and bind a Vertex Buffer Object (VBO) to store vertex data
5. Configure vertex attributes to specify how vertex data is interpreted
6. Set up a render loop to clear the screen and draw the triangle
7. Clean up resources and terminate GLFW upon exit
8. The program uses shaders loaded from external files to control the rendering process

---

## Source Code

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "shader_utils.h" // Assume this header contains functions to load and compile shaders

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Set window hints for OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS
#endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport size and framebuffer size callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Define vertex data for a triangle
    GLfloat postions[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    // Create and bind a Vertex Buffer Object (VBO) to store vertex data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(postions), postions, GL_STATIC_DRAW);

    // Configure vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 2,
        (void *)0
    );

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and delete allocated resources
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();
}
```
