#include "config.h"

/**
 * Table of Contents
 * chapter 1: basic openGL notes
 * chapter 2: openGL and libraries
 * chapter 3: Create Window with glfw and load openGL functions with glad
 * chapter 4: Graphics Pipeline
 * chapter 5: CPU-GPU communication
 * chapter 6: Element Buffer Object (EBO) and drawing with indices
 */

/* chapter 1: basic openGL notes
 *
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
 * opengl is a state machine, meaning that it maintains a large set of states
 * that affect how commands are processed. for example, the command to draw
 * something will behave differently depending on what shader program is
 * currently active, what textures are bound, what the blend mode is, etc.
 */
/**
 * chapter 2: openGL and libraries
 *
 * opengl itself is just a specification that defines a set of functions
 * and behaviors for rendering graphics. however, it does not provide any
 * functionality for creating windows, handling input, or loading resources.
 * therefore, in order to use openGL in a practical application, you typically
 * need to use it in conjunction with other libraries that provide these
 * functionalities. some common libraries used with openGL include:
 * - glfw: a library for creating windows, handling input, and managing openGL contexts.
 * - glad: a library for loading openGL function pointers at runtime.
 *       since openGL implementations can vary between different hardware and drivers,
 *       glad helps to ensure that your application can access the correct functions for
 *       the specific openGL version and extensions supported by the user's system.
 *
 * - glm: a mathematics library for graphics programming, providing
 * vector and matrix types and operations.
 * - assimp: a library for loading 3D models from various file formats.
 * - stb_image: a library for loading image files as textures.
 * these libraries help to simplify the process of using openGL by providing
 * higher-level abstractions and utilities for common tasks. they also help to
 * ensure that your application is portable across different platforms and
 * hardware configurations.
 */
/**
 * chapter 3: Create Window with glfw and load openGL functions with glad
 *
 * 1. initialize glfw library using glfwInit()
 * 2. set window hints to configure the openGL context version and profile
 *    using glfwWindowHint()
 * 3. create a window using glfwCreateWindow()
 * 4. make the created window's context current using glfwMakeContextCurrent()
 * 5. load openGL function pointers using gladLoadGLLoader()
 * 6. set the viewport size using glViewport()
 * 7. set a framebuffer size callback using glfwSetFramebufferSizeCallback()
 * 8. in the render loop:
 *    a. process input
 *    b. clear the screen
 *    c. draw the object
 *    d. swap buffers and poll events
 * 9. clean up and delete allocated resources
 * 10. terminate glfw using glfwTerminate()
 * 11. exit the program
 */
/**
 * chapter 4: Graphics Pipeline
 * the graphics pipeline is a conceptual model that describes the sequence
 * of steps involved in rendering a 3D scene to a 2D screen. it consists of
 * several stages, each responsible for a specific aspect of the rendering
 * process. the main stages of the graphics pipeline are:
 * 1. vertex processing: in this stage, the vertex data (positions, colors,
 *    texture coordinates, etc.) is processed by the vertex shader. the vertex
 *    shader transforms the vertex positions from model space to clip space,
 *    applies any necessary lighting calculations, and passes per-vertex
 *    attributes to the next stage.
 * 2. primitive assembly: in this stage, the processed vertices are assembled
 *    into geometric primitives (points, lines, triangles) based on the
 *    specified topology. this stage also performs clipping to remove any
 *    primitives that are outside the view frustum.
 * 3. rasterization: in this stage, the geometric primitives are converted
 *    into fragments (potential pixels) based on their coverage of the
 *    screen. each fragment contains information such as its position, depth,
 *    and interpolated per-vertex attributes.
 * 4. fragment processing: in this stage, the fragments are processed by the
 *    fragment shader. the fragment shader calculates the final color of
 *    each fragment based on lighting, texture data, and other factors. it
 *    may also perform operations such as alpha blending and depth testing.
 * 5. output merger: in this final stage, the processed fragments are merged
 *    into the framebuffer. this stage handles operations such as depth
 *    testing, stencil testing, and blending to determine the final color
 *    of each pixel on the screen.
 * by understanding the graphics pipeline, developers can gain insight
 * into how 3D scenes are rendered and how to optimize their applications
 * for better performance and visual quality.
 */

/** chapter 5: CPU-GPU communication
 * opengl is designed to leverage the parallel processing power of modern
 * graphics processing units (gpus). to achieve this, opengl uses a client-server
 * model, where the cpu (client) sends commands and data to the gpu (server)
 * for processing and rendering. this communication between the cpu and gpu is
 * facilitated through a set of buffers and objects that are managed by opengl.
 * key concepts:
 * vertex is a data structure that represents a single point in 3D space, along
 * with additional attributes such as color, texture coordinates, and normals.
 * vertices are the building blocks of 3D geometry, and they are used to define
 * the shape and appearance of objects in a scene.
 * example: a triangle is defined by three vertices, each with its own position
 * and color attributes.
 * buffer is a contiguous block of memory that is used to store data on the gpu.
 * buffers are used to hold vertex data, index data, texture data, and other
 * types of information that the gpu needs to render a scene. buffers are created
 * and managed by opengl, and they can be bound to different targets for
 * different purposes.
 * example: a vertex buffer object (vbo) is a type of buffer that holds vertex
 * data. it can be bound to the gl_array_buffer target, allowing the gpu to
 * access the vertex data during rendering.
 * attribute is a variable in a shader program that holds per-vertex data. attributes are used to pass information from the vertex buffer to the vertex shader, allowing the shader to process and transform the vertex data. each attribute has a specific location and data type, and it can be enabled or disabled as needed.
 * example: a vertex shader may have attributes for position, color, and texture
 * coordinates. these attributes are populated with data from the vertex buffer
 * during rendering.
 * shader is a small program that runs on the gpu and defines how to process
 * vertex and fragment data. shaders are written in a specialized language
 * called glsl (openGL shading language) and are compiled and linked into a
 * shader program that can be used for rendering.
 * example: a vertex shader may transform vertex positions from model space
 * to clip space, while a fragment shader may calculate the final color of
 * each pixel based on lighting and texture data.
 * draw call is a command sent from the cpu to the gpu to render geometry
 * using the specified vertex data and shaders. draw calls typically reference
 * the vertex array objects (vaos) and shader programs to determine how to
 * process and render the geometry.
 * example: the glDrawArrays function is a draw call that renders a set of
 * vertices as a series of primitives (e.g. triangles, lines, points) using
 * the currently bound vao and shader program.
 * in summary,
 * some key concepts related to cpu-gpu communication in opengl include:
 * - vertex buffer objects (vbos): these are memory buffers that store vertex
 *   data (e.g. positions, colors, texture coordinates) on the gpu. vbos allow
 *   for efficient transfer of vertex data from the cpu to the gpu, reducing
 *   the overhead of sending data for each draw call.
 * - vertex array objects (vaos): these are objects that encapsulate the state
 *   needed to specify vertex data for rendering. vaos store the configuration
 *   of vertex attributes (e.g. which vbos to use, how to interpret the data)
 *   and allow for easy switching between different vertex data setups.
 * - shaders: these are small programs that run on the gpu and define how to
 *   process vertex and fragment data. shaders are written in a specialized
 *   language called glsl (openGL shading language) and are compiled and linked
 *   into a shader program that can be used for rendering.
 * - draw calls: these are commands sent from the cpu to the gpu to render
 *   geometry using the specified vertex data and shaders. draw calls typically
 *   reference the vaos and shader programs to determine how to process and
 *   render the geometry.
 * by using these concepts and objects, opengl enables efficient communication
 * between the cpu and gpu, allowing for high-performance rendering of complex
 * graphics.
 *
 * let's expalin these concepts in more detail:
 * - Vertex Buffer Objects (VBOs):
 *   VBOs are memory buffers that store vertex data on the GPU. They allow for
 *   efficient transfer of vertex data from the CPU to the GPU, reducing the
 *   overhead of sending data for each draw call. VBOs are created and managed
 *   using OpenGL functions such as glGenBuffers, glBindBuffer, and glBufferData.
 *   Once a VBO is created and populated with vertex data, it can be bound to
 *   the GL_ARRAY_BUFFER target, allowing the GPU to access the vertex data
 *   during rendering.
 * - Vertex Array Objects (VAOs):
 *   VAOs are objects that encapsulate the state needed to specify vertex data
 *   for rendering. They store the configuration of vertex attributes, including
 *   which VBOs to use and how to interpret the data. VAOs allow for easy switching
 *   between different vertex data setups, as binding a VAO automatically
 *   restores the vertex attribute configuration stored in the VAO. VAOs are
 *   created and managed using OpenGL functions such as glGenVertexArrays,
 *   glBindVertexArray, glEnableVertexAttribArray, and glVertexAttribPointer.
 * - Shaders:
 *   Shaders are small programs that run on the GPU and define how to process
 *   vertex and fragment data. They are written in GLSL (OpenGL Shading Language)
 *   and are compiled and linked into a shader program that can be used for rendering.
 *   Vertex shaders process vertex data, transforming vertex positions and
 *   passing per-vertex attributes to the fragment shader. Fragment shaders
 *   calculate the final color of each pixel based on lighting, texture data,
 *   and other factors. Shaders are created and managed using OpenGL functions
 *   such as glCreateShader, glShaderSource, glCompileShader, glCreateProgram,
 *   and glLinkProgram.
 * - Draw Calls:
 *   Draw calls are commands sent from the CPU to the GPU to render geometry
 *   using the specified vertex data and shaders. Draw calls typically reference
 *   the VAOs and shader programs to determine how to process and render the geometry.
 *   Common draw call functions include glDrawArrays and glDrawElements, which
 *   render a set of vertices as a series of primitives (e.g., triangles, lines,
 *   points) using the currently bound VAO and shader program.
 *
 *  by using these concepts and objects, OpenGL enables efficient communication
 *  between the CPU and GPU, allowing for high-performance rendering of complex
 *  graphics.
 */
/** chapter 6: Element Buffer Object (EBO) and drawing with indices
 * An Element Buffer Object (EBO), also known as an Index Buffer Object (IBO),
 * is a type of buffer in OpenGL that stores indices used to specify the order
 * in which vertices are drawn. EBOs allow you to reuse vertex data by
 * referencing vertices multiple times through indices, which can help reduce
 * memory usage and improve rendering performance.
 * When using an EBO, you typically follow these steps:
 * 1. Create and bind a Vertex Array Object (VAO) to store the vertex
 *    attribute configuration.
 * 2. Create and bind a Vertex Buffer Object (VBO) to store the vertex data.
 * 3. Create and bind an Element Buffer Object (EBO) to store the index data.
 * 4. Upload the vertex data to the VBO using glBufferData.
 * 5. Upload the index data to the EBO using glBufferData.
 * 6. Configure the vertex attributes using glVertexAttribPointer and
 *    glEnableVertexAttribArray.
 * 7. In the render loop, bind the VAO and call glDrawElements to draw the
 *    geometry using the indices stored in the EBO.
 * Example:
 * ```cpp
 * // Define vertex data
 * float vertices[] = {
 *     // positions
 *     0.5f, 0.5f, 0.0f,   // top right
 *     0.5f, -0.5f, 0.0f,  // bottom right
 *     -0.5f, -0.5f, 0.0f, // bottom left
 *     -0.5f, 0.5f, 0.0f   // top left
 * };
 * // Define index data
 * unsigned int indices[] = {
 *     0, 1, 3, // first triangle
 *     1, 2, 3  // second triangle
 * };
 * // Create and bind VAO, VBO, and EBO
 * unsigned int VBO, VAO, EBO;
 * glGenVertexArrays(1, &VAO);
 * glGenBuffers(1, &VBO);
 * glGenBuffers(1, &EBO);
 * glBindVertexArray(VAO);
 * glBindBuffer(GL_ARRAY_BUFFER, VBO);
 * glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 * glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 * glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 * // Configure vertex attributes
 * glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
 * glEnableVertexAttribArray(0);
 * // Render loop
 * while (!glfwWindowShouldClose(window)) {
 *     // Clear the screen
 *     glClear(GL_COLOR_BUFFER_BIT);
 *     // Draw the geometry using the EBO
 *     glBindVertexArray(VAO);
 *     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 *     // Swap buffers and poll events
 *     glfwSwapBuffers(window);
 *     glfwPollEvents();
 * }
 * ```
 */

/*
 * basic openGL program structure
 * 1. initialize openGL context and create a window using a library like glfw
 * 2. load openGL function pointers using a library like glad
 * 3. set up vertex data and buffers and configure vertex attributes
 * 4. compile and link shaders into a shader program
 * 5. in the render loop:
 *    a. process input
 *    b. clear the screen
 *    c. use the shader program
 *    d. bind vertex array object (VAO)
 *    e. draw the object
 *    f. swap buffers and poll events
 * 6. clean up and delete allocated resources
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