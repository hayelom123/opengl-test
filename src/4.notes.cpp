#include "config.h"

/*
 * This file contains basic openGL notes
 *openGL is a state machine. meaning it maintains a large set of states that
 *affect how commands are processed. for example, the command to draw something
 *will behave differently depending on what shader program is currently active,
 *what textures are bound, what the blend mode is, etc.
 * There are many states in openGL, and they can be changed by calling various
 * openGL is specification functions.
 * openGL does not have a concept of a "default" state. when a context is
 * created, all states are initialized to default values defined by the openGL
 * specification. however, these default values may not be what you want for your
 * application, so it is important to explicitly set the states you care about.
 * openGL is a set of state and commands that operate on that state.
 * The openGL specification defines a large number of states that can be set and
 * queried, as well as a large number of commands that operate on those states.
 * Some examples of openGL states include:
 * - The current shader program
 * - The current bound textures
 * - The current blend mode
 * - The current depth test function
 * - The current viewport size
 * Some examples of openGL commands include:
 * - Drawing commands (e.g. glDrawArrays, glDrawElements)
 * - State-setting commands (e.g. glEnable, glDisable, glBlendFunc)
 * - Resource management commands (e.g. glGenBuffers, glBindBuffer, glBufferData)
 * In order to use openGL effectively, it is important to understand how to
 * manage its state and how to use its commands to achieve the desired rendering
 * effects.
 * opengl is a low-level graphics API that provides a set of functions for rendering
 * 2D and 3D graphics. it is designed to be platform-independent and hardware-
 * agnostic, allowing developers to create graphics applications that can run on
 * a wide range of devices.
 * opengl is often used in conjunction with other libraries and frameworks,
 * such as glfw for window management and input handling, and glad for loading
 * openGL function pointers.
 * opengl is widely used in the development of video games, simulations,
 * and other graphics-intensive applications.
 * it provides a powerful and flexible set of tools for creating high-quality
 * graphics, but it also requires a good understanding of computer graphics
 * concepts and programming techniques.
 */

const int WIDTH = 800;
const int HEIGHT = 600;

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // draw traingle
    GLfloat postions[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f};

    /*
     a vertex buffer object (VBO) is created here. this stores an array of
     data on the graphics adapter's memory. in our case - the vertex points
    */
    unsigned int VBO; // unsigned int

    // this generates one memory buffer because we specified 1 and returns the id of generated buffer(memory on GPU).
    glGenBuffers(1, &VBO);                                                     // gives you a name (ID)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        // selects that name
                                                                               // the size is the total data_size_in_bytes is the size in bytes of your vertex data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(postions), postions, GL_STATIC_DRAW); // fills it with data // Allocate memory and upload data

    /*
    the vertex array object (VAO) is a little descriptor that defines which
    data from vertex buffer objects should be used as input variables to vertex
    shaders. in our case - use our only VBO, and say 'every three floats is a
    variable'
     */
    // unsigned int VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    /* "attribute #0 should be enabled when this VAO is bound" */
    glEnableVertexAttribArray(0);
    /*
        this VBO is already bound, but it's a good habit to explicitly specify which
        VBO's data the following vertex attribute pointer refers to
    */
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /* "attribute #0 is created from every 3 variables in the above buffer, of type
    float (i.e. make me vec3s)" */
    //  index,count,type,normalize,stride->the size of each vertices(2*float)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // glClear(GL_COLOR_BUFFER_BIT);
    // glBindBuffer(GL_TRIANGLES, 0);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}