# chapter 3: Create Window with glfw and load openGL functions with glad

1. initialize glfw library using glfwInit()
2. set window hints to configure the openGL context version and profile
   using glfwWindowHint()
3. create a window using glfwCreateWindow()
4. make the created window's context current using glfwMakeContextCurrent()
5. load openGL function pointers using gladLoadGLLoader()
6. set the viewport size using glViewport()
7. set a framebuffer size callback using glfwSetFramebufferSizeCallback()
8. in the render loop:
   a. process input
   b. clear the screen
   c. draw the object
   d. swap buffers and poll events
9. clean up and delete allocated resources
10. terminate glfw using glfwTerminate()
11. exit the program
