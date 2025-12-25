#include "config.h"

/// @details https://www.geeksforgeeks.org/blogs/opengl-rendering-pipeline-overview/

void framebuffer_size_callback(GLFWwindow *window, int width, int height)

{
    std::cout << "Framebuffer resized: " << width << "x" << height << std::endl;
    glViewport(0, 0, width, height);
}

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";
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

    // Vertices coordinates
    GLfloat vertices[] =
        {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,   // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
        };

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
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // create shaders

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); // compile the vertex shader

    // create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader); // compile the fragment shader

    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // generate buffer id
    GLuint VBO, VAO; // Vertex Buffer Object, Vertex Array Object
    // defnition of the VAO and VBO and what they are used for can be found in the "Vertex Specification" section
    /*
    Why: OpenGL uses small integer handles (IDs) to refer to GPU objects.
    You must create these handles before binding or using the objects.
    The VAO will remember how vertex attributes are laid out;
    the VBO will hold the raw vertex bytes.
    */
    glGenVertexArrays(1, &VAO); // asks OpenGL to generate 1 Vertex Array Object ID and store it in VAO.
    glGenBuffers(1, &VBO);      // generates 1 Buffer Object ID (we’ll use it as a Vertex Buffer Object) and stores it in VBO

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    // render loop
    // --------------------------------
    // tell opengl to use the shader program
    glUseProgram(shaderProgram);
    // bind the VAO (the triangle)
    glBindVertexArray(VAO);
    // draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // unbind the VAO
    glBindVertexArray(0);

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

/*

With the vertex data defined we'd like to send it as input to the first process of the graphics pipeline: the vertex shader.
This is done by creating memory on the GPU where we store the vertex data, configure how OpenGL should interpret the memory 
and specify how to send the data to the graphics card. The vertex shader then processes as much vertices as we tell it to from its memory.

*/