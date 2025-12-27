# chapter 6: Element Buffer Object (EBO) and drawing with indices

An Element Buffer Object (EBO), also known as an Index Buffer Object (IBO),
is a type of buffer in OpenGL that stores indices used to specify the order
in which vertices are drawn.

EBOs allow you to reuse vertex data by referencing vertices multiple times
through indices, which can help reduce memory usage and improve rendering
performance.

When using an EBO, you typically follow these steps:

1. Create and bind a Vertex Array Object (VAO)
2. Create and bind a Vertex Buffer Object (VBO)
3. Create and bind an Element Buffer Object (EBO)
4. Upload the vertex data to the VBO
5. Upload the index data to the EBO
6. Configure the vertex attributes
7. Draw using glDrawElements

```cpp
float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};
```
