#include "config.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Specify the color of the background
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {

        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}

/*

Example: Drawing a Simple Triangle
Let’s see the pipeline in action with a simple triangle:

1.Vertex Specification: Define three vertices with positions and colors (e.g., red, blue, green).
2.Vertex Shader: Place the vertices in the 3D world, adjusting for the camera.
3.Primitive Assembly: Connect the vertices to form a triangle.
4.Rasterization: Turn the triangle into fragments for the pixels it covers.
5.Fragment Shader: Blend the colors across the triangle (e.g., fading from red to blue).
6.Per-Sample Operations: Check depth (if needed) and display the triangle.

*/