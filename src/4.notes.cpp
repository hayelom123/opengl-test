#include "config.h"

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