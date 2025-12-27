# Chapter 5: CPU–GPU Communication

OpenGL uses a client–server model:

- CPU sends commands and data
- GPU executes rendering operations

## Core Concepts

### Vertex

A data structure representing a point in 3D space, including attributes like:

- Position
- Color
- Texture coordinates
- Normals

### Buffer

A contiguous block of GPU memory used to store:

- Vertex data
- Index data
- Texture data

### Attribute

Per-vertex data passed from buffers to shaders.

### Shader

A small program running on the GPU, written in GLSL.

- Vertex shader
- Fragment shader

### Draw Call

A command issued by the CPU to render geometry.
Examples:

- `glDrawArrays`
- `glDrawElements`

## Key OpenGL Objects

- **VBO (Vertex Buffer Object)** – stores vertex data
- **VAO (Vertex Array Object)** – stores vertex attribute configuration
- **Shaders** – define rendering behavior
- **Draw Calls** – trigger rendering
