# This is opengl training ground with c++
### we have used cmakeLists.txt for file management

### we follow the following resources 
  - https://learnopengl.com/Getting-started/Hello-Triangle
  - https://antongerdelan.net/opengl/shaders.html
  - https://antongerdelan.net/opengl/hellotriangle.html
  - https://youtu.be/W3gAzLwfIP0?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2

## pre request
 - basic understanding of c++ specially pointers and references
 - understanding basic programming

## before you start reading watch the following youtube video

- [How do Video Game Graphics Work?](https://www.youtube.com/watch?v=C8YtdC8mxTU)

 <div align="center">

<a href="https://www.youtube.com/watch?v=C8YtdC8mxTU" target="_blank" rel="noopener noreferrer">
  <img src="https://img.youtube.com/vi/C8YtdC8mxTU/maxresdefault.jpg" alt="Watch the video" width="100%"/>
</a>

</div>


# What is opengl

  OpenGL is mainly considered an  _API (an Application Programming Interface)_ that provides us with a large set of functions that we can use to manipulate graphics and images. However, OpenGL by itself is not an API, but merely a _specification_, developed and maintained by the Khronos Group.


  The OpenGL specification specifies exactly what the _result/output_ of each function should be and how it should perform. It is then up to the developers implementing this specification to come up with a solution of how this function should operate. Since the OpenGL specification does not give us implementation details, the actual developed versions of OpenGL are allowed to have different implementations, as long as their results comply with the specification (and are thus the same to the user).

  The _people developing_ the actual OpenGL libraries are usually the _graphics card manufacturers_. Each graphics card that you buy supports specific versions of OpenGL which are the versions of OpenGL developed specifically for that card (series). When using an Apple system the OpenGL library is maintained by Apple themselves and under Linux there exists a combination of graphic suppliers' versions and hobbyists' adaptations of these libraries. This also means that whenever OpenGL is showing weird behavior that it shouldn't, this is most likely the fault of the graphics cards manufacturers (or whoever developed/maintained the library).

  ## Core-profile vs Immediate mode

  **Core-profile** - the latest specification of openGL (version 3.2 on ward)
  
  **Immediate mode** - the old specification of openGL (pre 3.2 version)
  
  In the old days, using OpenGL meant developing in immediate mode (often referred to as the fixed function pipeline) which was an easy-to-use method for drawing graphics. Most of the functionality of OpenGL was hidden inside the library and developers did not have much control over how OpenGL does its calculations. Developers eventually got hungry for more flexibility and over time the specifications became more flexible as a result; developers gained more control over their graphics. The immediate mode is really easy to use and understand, but it is also extremely inefficient. For that reason the specification started to deprecate immediate mode functionality from version 3.2 onwards and started motivating developers to develop in OpenGL's core-profile mode, which is a division of OpenGL's specification that removed all old deprecated functionality.

When using OpenGL's core-profile, OpenGL forces us to use modern practices. Whenever we try to use one of OpenGL's deprecated functions, OpenGL raises an error and stops drawing. The advantage of learning the modern approach is that it is very flexible and efficient. However, it's also more difficult to learn. The immediate mode abstracted quite a lot from the actual operations OpenGL performed and while it was easy to learn, it was hard to grasp how OpenGL actually operates. The modern approach requires the developer to truly understand OpenGL and graphics programming and while it is a bit difficult, it allows for much more flexibility, more efficiency and most importantly: a much better understanding of graphics programming.

This is also the reason why this book is geared at core-profile OpenGL version 3.3. Although it is more difficult, it is greatly worth the effort.

As of today, higher versions of OpenGL are available to choose from (at the time of writing 4.6) at which you may ask: why do I want to learn OpenGL 3.3 when OpenGL 4.6 is out? The answer to that question is relatively simple. All future versions of OpenGL starting from 3.3 add extra useful features to OpenGL without changing OpenGL's core mechanics; the newer versions just introduce slightly more efficient or more useful ways to accomplish the same tasks. The result is that all concepts and techniques remain the same over the modern OpenGL versions so it is perfectly valid to learn OpenGL 3.3. Whenever you're ready and/or more experienced you can easily use specific functionality from more recent OpenGL versions.


***
```diff
+ [!IMPORTANT]  
+ When using functionality from the most recent version of OpenGL, only the most modern graphics cards will be able to run your application.  
+ This is often why most developers generally target lower versions of OpenGL and optionally enable higher version functionality.
```
***

## State machine

OpenGL is by itself a large state machine: a collection of variables that define how OpenGL should currently operate. The state of OpenGL is commonly referred to as the OpenGL context. When using OpenGL, we often change its state by setting some options, manipulating some buffers and then render using the current context.

Whenever we tell OpenGL that we now want to draw lines instead of triangles for example, we change the state of OpenGL by changing some context variable that sets how OpenGL should draw. As soon as we change the context by telling OpenGL it should draw lines, the next drawing commands will now draw lines instead of triangles.

When working in OpenGL we will come across several state-changing functions that change the context and several state-using functions that perform some operations based on the current state of OpenGL. As long as you keep in mind that OpenGL is basically one large state machine, most of its functionality will make more sense.

## Objects

The OpenGL libraries are written in C and allows for many derivations in other languages, but in its core it remains a C-library. Since many of C's language-constructs do not translate that well to other higher-level languages, OpenGL was developed with several abstractions in mind. One of those abstractions are objects in OpenGL.

An object in OpenGL is a collection of options that represents a subset of OpenGL's state. For example, we could have an object that represents the settings of the drawing window; we could then set its size, how many colors it supports and so on. One could visualize an object as a C-like struct:

```c++
     struct object_name {
          float  option1;
          int    option2;
          char[] name;
      };

```

Whenever we want to use objects it generally looks something like this (with OpenGL's context visualized as a large struct):

```c++
// The State of OpenGL
struct OpenGL_Context {
  	...
  	object_name* object_Window_Target;
  	...  	
};
```

# Creating a window

The first thing we need to do before we start creating stunning graphics is to create an OpenGL context and an application window to draw in. However, those operations are specific per operating system and OpenGL purposefully tries to abstract itself from these operations. This means we have to create a window, define a context, and handle user input all by ourselves.

Luckily, there are quite a few libraries out there that provide the functionality we seek, some specifically aimed at OpenGL. Those libraries save us all the operation-system specific work and give us a window and an OpenGL context to render in. Some of the more popular libraries are GLUT, SDL, SFML and GLFW. On LearnOpenGL we will be using GLFW. Feel free to use any of the other libraries, the setup for most is similar to GLFW's setup.



# GLFW

GLFW is a library, written in C, specifically targeted at OpenGL. GLFW gives us the bare necessities required for rendering goodies to the screen. It allows us to create an OpenGL context, define window parameters, and handle user input, which is plenty enough for our purposes.

The focus of this and the next chapter is to get GLFW up and running, making sure it properly creates an OpenGL context and that it displays a simple window for us to mess around in. This chapter takes a step-by-step approach in retrieving, building and linking the GLFW library.

GLFW can be obtained from their webpage's [download](http://www.glfw.org/download.html) page.

# GLAD
Because OpenGL is only really a standard/specification it is up to the driver manufacturer to implement the specification to a driver that the specific graphics card supports. Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time. It is then the task of the developer to retrieve the location of the functions he/she needs and store them in function pointers for later use. Retrieving those locations is OS-specific. In Windows it looks something like this:

```c++
// define the function's prototype
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// find the function and assign it to a function pointer
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// function can now be called as normal
unsigned int buffer;
glGenBuffers(1, &buffer);
```
 As you can see the code looks complex and it's a cumbersome process to do this for each function you may need that is not yet declared. Thankfully, there are libraries for this purpose as well where GLAD is a popular and up-to-date library.

## Setting up GLAD
GLAD is an [open](https://github.com/Dav1dde/glad) source library that manages all that cumbersome work we talked about. GLAD has a slightly different configuration setup than most common open source libraries. GLAD uses a web service where we can tell GLAD for which version of OpenGL we'd like to define and load all relevant OpenGL functions according to that version.

Go to the GLAD web [service](http://glad.dav1d.de/), make sure the language is set to C++, and in the API section select an OpenGL version of at least 3.3 (which is what we'll be using; higher versions are fine as well). Also make sure the profile is set to Core and that the Generate a loader option is ticked. Ignore the extensions (for now) and click Generate to produce the resulting library files.

GLAD by now should have provided you a zip file containing two include folders, and a single glad.c file. Copy both include folders (glad and KHR) into your include(s) directoy (or add an extra item pointing to these folders), and add the glad.c file to your project.

similar to this project file structure

# Hello Window

Let's see if we can get GLFW up and running. First, create a .cpp file and add the following includes to the top of your newly created file.

```c++
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```
[!NOTE]
Be sure to include GLAD before GLFW. The include file for GLAD includes the required OpenGL headers behind the scenes (like GL/gl.h) so be sure to include GLAD before other header files that require OpenGL (like GLFW).

Next, we create the main function where we will instantiate the GLFW window:

```c++
int main()
{
    glfwInit();
    // setting up the opnGK version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// setting major version to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// minor version .3 
    // we have set it up to core profile of opengl
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // for mac or apple devices uncomment the following code  
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
    return 0;
}
```
In the main function we first initialize GLFW with _glfwInit_, after which we can configure GLFW using _glfwWindowHint_. The first argument of glfwWindowHint tells us what option we want to configure, where we can select the option from a large enum of possible options prefixed with GLFW_. The second argument is an integer that sets the value of our option. A list of all the possible options and its corresponding values can be found at GLFW's window handling documentation. If you try to run the application now and it gives a lot of undefined reference errors it means you didn't successfully link the GLFW library.

 <h2>glfwInit</h2><h3>GLFW</h3><p><p>
  This function initializes the GLFW library. Before most GLFW functions can be used, GLFW must be initialized.</p>
<p>
  The function returns <code>GL_TRUE</code> if succesfull, otherwise <code>GL_FALSE</code> is returned when an error occured.
</p>
</p>

<h2>glfwWindowHint</h2><h3>GLFW</h3><p><p>
  This function sets hints for the next call to <code>glfwCreateWindow</code>. The hints, once set, retain their values until changed by a another call to <code>glfwWindowHint</code>.
</p>

<p>
  The parameters of <code>glfwWindowHint(int target, int hint)</code> are as follows:
  <ul>
    <li><code>target</code>: sets the target/option that we want to change. Targets are set using one of GLFW's enums prefixed with <code>GLFW_</code>.</li>
    <li><code>hint</code>: the value/hint of the target that we want to set. </li>
  </ul>
</p>

<h4>Example usage</h4>
<pre class="cpp"><code>
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);  
</code></pre></p>

<p>
  Since the focus of this book is on OpenGL version 3.3 we'd like to tell GLFW that 3.3 is the OpenGL version we want to use. This way GLFW can make the proper arrangements when creating the OpenGL context. This ensures that when a user does not have the proper OpenGL version GLFW fails to run. We set the major and minor version both to <code>3</code>. We also tell GLFW we want to explicitly use the core-profile. Telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need. Note that on Mac OS X you need to add <code><function id="18">glfwWindowHint</function>(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);</code> to your initialization code for it to work.
</p>


> [!NOTE]  
> Make sure you have OpenGL versions 3.3 or higher installed on your system/hardware otherwise the application will crash or display
> undefined behavior. To find the OpenGL version on your machine either call <strong>glxinfo</strong> on Linux machines or use a utility >like the <a href="http://download.cnet.com/OpenGL-Extensions-Viewer/3000-18487_4-34442.html" target="_blank">OpenGL Extension Viewer</a> >for Windows. If your supported version is lower try to check if your video card supports OpenGL 3.3+ (otherwise it's really old) and/or >update your drivers.

Next we're required to create a window object. This window object holds all the windowing data and is required by most of GLFW's other functions.

```c++

GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window);

```
The glfwCreateWindow function requires the window width and height as its first two arguments respectively. The third argument allows us to create a name for the window; for now we call it "LearnOpenGL" but you're allowed to name it however you like. We can ignore the last 2 parameters. The function returns a GLFWwindow object that we'll later need for other GLFW operations. After that we tell GLFW to make the context of our window the main context on the current thread.

<h2>glfwCreateWindow</h2><h3>GLFW</h3><p><p>
  This function creates a window and its associated context. Most of the options controlling how the window and its context should be created are specified through glfwWindowHint.
</p>

<p>
  Successful creation does not change which context is current. Before you can use the newly created context, you need to make it current using glfwMakeContextCurrent.
</p>

<p>
  The parameters of <code>glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share )</code> are as follows:
  <ul>
    <li><code>width</code>: The desired width, in screen coordinates, of the window.</li>
    <li><code>height</code>: The desired height, in screen coordinates, of the window.</li>
    <li><code>title</code>: The initial window title.</li>
    <li><code>monitor</code>: The monitor to use for full screen mode, or <code>NULL</code> to use windowed mode.</li>
    <li><code>share</code>: The window whose context to share resources with, or <code>NULL</code> to not share resources.</li>
  </ul>
</p>

<p>
  The function returns a pointer to a <code>GLFWwindow</code> object that is required for other GLFW operations.
</p>

<h4>Example usage</h4>
<pre class="cpp"><code>
GLFWwindow* window;
window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
</code></pre></p>

## GLAD
In the previous chapter we mentioned that GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function:

```c++
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
} 
```
We pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific. GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.

## Viewport
Before we can start rendering we have to do one last thing. We have to tell OpenGL the size of the rendering window so OpenGL knows how we want to display the data and coordinates with respect to the window. We can set those dimensions via the glViewport function:

```c++
glViewport(0, 0, 800, 600);
```

<h2>glViewport</h2><h3>Initialization</h3><p><p>
  This function specifies the actual window rectangle for your renderings. The function requires 4 coordinates for the left, bottom, right and top coordinate of your viewport rectangle. The coordinates specified tell OpenGL how it should map its <em>normalized device coordinates</em> (in the range -1 to 1) to <em>window coordinates</em> (in the range as specified by the given coordinates).
</p>

<p>
  Note that the y-coordinate starts at the bottom of the viewport. If <code>y = 0</code>, it's at the bottom of the viewport.
</p>

<p>
  The parameters of <code>glViewport(GLint x, GLint y, GLsizei width, GLsizei height)</code> are as follows:
  <ul>
    <li><code>x</code>: The left x-coordinate of the viewport rectangle. </li>
    <li><code>y</code>: The bottom y-coordinate of the viewport rectangle. </li>
    <li><code>width</code>: The width of the viewport.</li>
    <li><code>height</code> The height of the viewport.</li>
  </ul>
</p></p>

We could actually set the viewport dimensions at values smaller than GLFW's dimensions; then all the OpenGL rendering would be displayed in a smaller window and we could for example display other elements outside the OpenGL viewport.

> [!NOTE]
 Behind the scenes OpenGL uses the data specified via <fun><function id="22">glViewport</function></fun> to transform the 2D coordinates it processed to coordinates on your screen. For example, a processed point of location <code>(-0.5,0.5)</code> would (as its final transformation) be mapped to <code>(200,450)</code> in screen coordinates. Note that processed coordinates in OpenGL are between -1 and 1 >so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).

However, the moment a user resizes the window the viewport should be adjusted as well. We can register a callback function on the window that gets called each time the window is resized. This resize callback function has the following prototype:

<pre><code class=" hljs cpp">
<span class="hljs-keyword">void</span> framebuffer_size_callback(GLFWwindow* window, <span class="hljs-keyword">int</span> width, <span class="hljs-keyword">int</span> height);  
</code></pre>

The framebuffer size function takes a GLFWwindow as its first argument and two integers indicating the new window dimensions. Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process.

```c++
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
```
We do have to tell GLFW we want to call this function on every window resize by registering it:

```c++
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
```

When the window is first displayed framebuffer_size_callback gets called as well with the resulting window dimensions. For retina displays width and height will end up significantly higher than the original input values.

There are many callbacks functions we can set to register our own functions. For example, we can make a callback function to process joystick input changes, process error messages etc. We register the callback functions after we've created the window and before the render loop is initiated.

## Ready your engines

We don't want the application to draw a single image and then immediately quit and close the window. We want the application to keep drawing images and handling user input until the program has been explicitly told to stop. For this reason we have to create a while loop, that we now call the render loop, that keeps on running until we tell GLFW to stop. The following code shows a very simple render loop:

```c++
while(!glfwWindowShouldClose(window))
{
    glfwSwapBuffers(window);
    glfwPollEvents();    
}
```

The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW has been instructed to close. If so, the function returns true and the render loop stops running, after which we can close the application.
The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events), updates the window state, and calls the corresponding functions (which we can register via callback methods). The glfwSwapBuffers will swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.

<h2>glfwWindowShouldClose</h2><h3>GLFW</h3><p><p>
  <code>GLboolean glfwWindowShouldClose(GLFWwindow* window)</code> takes the window object as its argument and returns <code>GL_TRUE</code> if the window has been instructed to close. The function will thus continously return <code>GL_FALSE</code> until instructed otherwise. 
</p>

<h4>Example usage</h4>
<pre><code>
while(!glfwWindowShouldClose(window))
{
  // Poll for events
  // Render stuff
  // Swap buffers
} 
</code></pre></p>

<h2>glfwPollEvents</h2>
<h3>GLFW</h3>
<p>
<p>This function processes those events that have been received and then returns immediately. Processing events will cause the window and input callbacks associated with those events to be called.
</p>
</p>

<h2>glfwSwapBuffers</h2>
<h3>GLFW</h3>
<p>
<p>This function swaps the front and back buffers of the specified window's double-buffer. 
</p>
 
> [!NOTE]
>  **Double buffer**
> 
> When an application draws in a single buffer the resulting image may display flickering issues. This is because the resulting output image is not drawn in an instant, but drawn pixel by pixel and usually from left to right and top to bottom. Because this image is not displayed at an instant to the user while still being rendered to, the result may contain artifacts. To circumvent these issues, windowing applications apply a double buffer for rendering. The front buffer contains the final output image that is shown at the screen, while all the rendering commands draw to the back buffer. As soon as all the rendering commands are finished we swap the back buffer to the front >buffer so the image can be displayed without still being rendered to, removing all the aforementioned artifacts.

</p>


### One last thing
As soon as we exit the render loop we would like to properly clean/delete all of GLFW's resources that were allocated. We can do this via the ***glfwTerminate*** function that we call at the end of the main function.

```c++
glfwTerminate();
return 0;
```

This will clean up all the resources and properly exit the application. Now try to compile your application and if everything went well you should see the following output:

<h2>glfwTerminate</h2><h3>GLFW</h3><p><p>
  This function destroys all remaining windows, frees any allocated resources and sets the library to an uninitialized state. Once this is called, you must again call glfwInit successfully before you will be able to use most GLFW functions.
</p>

<p>
  It is generally good practice to clean up your resources. As soon as the user exits the game loop you should call <code>glfwTerminate</code> and exit the application.
</p></p>













