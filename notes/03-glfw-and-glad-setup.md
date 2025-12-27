# Chapter 3: Creating a Window with GLFW and Loading OpenGL with GLAD

## Typical Initialization Steps

1. Initialize GLFW
2. Set OpenGL version and profile using window hints
3. Create a window
4. Make the window's OpenGL context current
5. Load OpenGL functions using GLAD
6. Set the viewport size
7. Register framebuffer resize callback
8. Enter the render loop:
   - Process input
   - Clear the screen
   - Draw objects
   - Swap buffers
   - Poll events
9. Clean up resources
10. Terminate GLFW
11. Exit the program
