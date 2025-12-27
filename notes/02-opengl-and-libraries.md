# chapter 2: openGL and libraries

opengl itself is just a specification that defines a set of functions
and behaviors for rendering graphics. however, it does not provide any
functionality for creating windows, handling input, or loading resources.

therefore, in order to use openGL in a practical application, you typically
need to use it in conjunction with other libraries that provide these
functionalities.

some common libraries used with openGL include:

- glfw: a library for creating windows, handling input, and managing openGL contexts.

- glad: a library for loading openGL function pointers at runtime.
  since openGL implementations can vary between different hardware and drivers,
  glad helps to ensure that your application can access the correct functions for
  the specific openGL version and extensions supported by the user's system.

- glm: a mathematics library for graphics programming, providing
  vector and matrix types and operations.

- assimp: a library for loading 3D models from various file formats.

- stb_image: a library for loading image files as textures.

these libraries help to simplify the process of using openGL by providing
higher-level abstractions and utilities for common tasks. they also help to
ensure that your application is portable across different platforms and
hardware configurations.
