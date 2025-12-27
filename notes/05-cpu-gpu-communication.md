# chapter 5: CPU-GPU communication

opengl is designed to leverage the parallel processing power of modern
graphics processing units (gpus). to achieve this, opengl uses a client-server
model, where the cpu (client) sends commands and data to the gpu (server)
for processing and rendering.

this communication between the cpu and gpu is facilitated through a set
of buffers and objects that are managed by opengl.

key concepts:

vertex is a data structure that represents a single point in 3D space, along
with additional attributes such as color, texture coordinates, and normals.

vertices are the building blocks of 3D geometry, and they are used to define
the shape and appearance of objects in a scene.

example: a triangle is defined by three vertices, each with its own position
and color attributes.

buffer is a contiguous block of memory that is used to store data on the gpu.

buffers are used to hold vertex data, index data, texture data, and other
types of information that the gpu needs to render a scene.

buffers are created and managed by opengl, and they can be bound to different
targets for different purposes.

example: a vertex buffer object (vbo) is a type of buffer that holds vertex
data.

it can be bound to the gl_array_buffer target, allowing the gpu to access the
vertex data during rendering.

attribute is a variable in a shader program that holds per-vertex data.

attributes are used to pass information from the vertex buffer to the vertex
shader, allowing the shader to process and transform the vertex data.

each attribute has a specific location and data type, and it can be enabled
or disabled as needed.

example: a vertex shader may have attributes for position, color, and texture
coordinates.

shader is a small program that runs on the gpu and defines how to process
vertex and fragment data.

shaders are written in a specialized language called glsl (openGL shading
language) and are compiled and linked into a shader program that can be used
for rendering.

draw call is a command sent from the cpu to the gpu to render geometry
using the specified vertex data and shaders.

example: glDrawArrays renders a set of vertices as primitives using the
currently bound vao and shader program.
