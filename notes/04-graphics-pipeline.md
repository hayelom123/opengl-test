# Chapter 4: Graphics Pipeline

The graphics pipeline describes the steps used to convert 3D data into a 2D image.

## Pipeline Stages

### 1. Vertex Processing

- Handled by the vertex shader
- Transforms vertices from model space to clip space
- Passes attributes to later stages

### 2. Primitive Assembly

- Groups vertices into points, lines, or triangles
- Performs clipping against the view frustum

### 3. Rasterization

- Converts primitives into fragments
- Interpolates vertex attributes

### 4. Fragment Processing

- Handled by the fragment shader
- Computes final color using lighting and textures
- Applies blending and depth testing

### 5. Output Merger

- Performs depth and stencil testing
- Writes final pixels to the framebuffer

Understanding the pipeline helps with optimization and debugging.
