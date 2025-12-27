# Chapter 2: OpenGL and Libraries

OpenGL itself is only a **specification**.  
It does not provide functionality for:

- Window creation
- Input handling
- Resource loading

To build real applications, OpenGL is used together with other libraries.

## Common OpenGL Libraries

### GLFW

- Window creation
- Input handling
- OpenGL context management

### GLAD

- Loads OpenGL function pointers at runtime
- Handles different OpenGL versions and drivers

### GLM

- Mathematics library
- Vector and matrix operations

### Assimp

- Loads 3D models from various formats

### stb_image

- Loads image files for textures

These libraries simplify OpenGL development and improve portability.
