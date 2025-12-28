# Chapter 7: Hello World Window with OpenGL Context

This chapter demonstrates how to create a basic window with an OpenGL context
using **GLFW** and **GLAD**. This is the foundation for any OpenGL application.

---

## Objectives

By the end of this chapter, you will be able to:

1. Initialize the GLFW library
2. Configure the OpenGL context version and profile
3. Create a window using `glfwCreateWindow`
4. Make the OpenGL context current
5. Load OpenGL function pointers using GLAD
6. Set the viewport size
7. Run a basic render loop
8. Properly clean up resources and terminate GLFW

---

## Steps Overview

1. Initialize GLFW
2. Set window hints for OpenGL version and profile
3. Create a window
4. Make the window’s OpenGL context current
5. Load OpenGL functions using GLAD
6. Set the viewport
7. Enter the render loop:
   - Process input
   - Clear the screen
   - (Placeholder) draw a triangle
   - Swap buffers and poll events
8. Destroy the window
9. Terminate GLFW and exit

---

## Full Example: Creating a Window with an OpenGL Context

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    // 1. Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. Set window hints for OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif

    // 3. Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 4. Make the window's context current
    glfwMakeContextCurrent(window);

    // 5. Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 6. Set the viewport size
    glViewport(0, 0, 800, 600);

    // 7. Render loop
    while (!glfwWindowShouldClose(window))
    {
        // a. Process input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // b. Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // c. Draw here (e.g., draw a triangle)

        // d. Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 8. Clean up and delete allocated resources
    glfwDestroyWindow(window);

    // 9. Terminate GLFW
    glfwTerminate();

    return 0;
}
```
