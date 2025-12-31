#include "config.h"
#include "utils.h"

#include <vector>
#include <cmath>

// draw circle
int width = 800, height = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    width = width;
    height = height;
    glViewport(0, 0, width, height);
}

int main()
{

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // load shaders
    std::string vertexShaderPath = "../shaders/triangles/triangle.vert";
    std::string fragmentShaderPath = "../shaders/triangles/triangle.frag";

    std::string vertexCode = loadShaderSourceFromFile(vertexShaderPath);
    std::string fragmentCode = loadShaderSourceFromFile(fragmentShaderPath);

    unsigned int shaderProgram = createShader(
        vertexCode,
        fragmentCode);
    /*
      0.0f,0.5f,// Top vertex
             //\\
             //  \\
- 0.5f,0.2f //____\\ 0.5f,0.2f
             || ||
-0.4f,-0.5f. ||_||0.4f,-0.5f
    */

    // drawing tradtional house shape with EBO
    // float vertices[] = {
    //     // the first triangle (roof)
    //     0.0f,
    //     0.8f, // Top vertex
    //     -0.5f,
    //     0.2f, // bottom-left
    //     0.5f,
    //     0.2f, // Top-right

    //     // bottom rectangle
    //     // left rectangle
    //     -0.4f,
    //     0.2f, // left-top
    //     -0.4f,
    //     -0.5f, // right-bottom
    //     0.4f,
    //     0.2f, // left-bottom
    //           // right rectangle
    //     -0.4f,
    //     -0.5f, // right-bottom
    //     0.4f,
    //     -0.5f,
    //     0.4f,
    //     0.2f,

    // };

    //
    float vertices[] = {
        // x, y
        0.0f, 0.8f,  // 0 roof top
        -0.5f, 0.2f, // 1 roof left
        0.5f, 0.2f,  // 2 roof right

        -0.4f, 0.2f, // 3 rect top-left
        0.4f, 0.2f,  // 4 rect top-right
        0.4f, -0.5f, // 5 rect bottom-right
        -0.4f, -0.5f // 6 rect bottom-left
    };
    unsigned int indices[] = {
        // roof
        0, 1, 2,

        // rectangle
        3, 6, 5,
        3, 5, 4};

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float),
                 vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int),
                 indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(vertices) / (2 * sizeof(float)));
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
// ----------------------------------------------------------------------
/**
 * Great question. I’ll explain **Element Buffer Objects (EBOs)** from **zero**, slowly, clearly, and **without assuming any prior knowledge**.

Think of this as **mental model first, OpenGL second**.

---

# 🧠 The Core Problem EBO Solves

### Without EBO (bad / wasteful)

If you draw a square using triangles **without** an EBO, you do this:

```cpp
// 2 triangles → 6 vertices (duplicated)
A, B, C,
C, D, A
```

But notice:

* Vertex **A** is used **twice**
* Vertex **C** is used **twice**

➡ You are **duplicating data**.

---

# ✅ What an Element Buffer Object (EBO) Is

An **EBO** is simply:

> **A buffer that stores indices, not vertex data**

Instead of sending the same vertex many times, you:

1. Send **each vertex once**
2. Tell OpenGL **which vertices to reuse**

---

# 📦 Three Buffers, Three Roles

| Object  | Stores      | Purpose                    |
| ------- | ----------- | -------------------------- |
| **VBO** | Vertex data | Positions, colors, normals |
| **EBO** | Indices     | Order of drawing           |
| **VAO** | State       | Remembers VBO + EBO layout |

---

# 🧩 Real Example (Square)

### Step 1 — Vertex data (unique only)

```cpp
float vertices[] = {
    // positions
    -0.5f, -0.5f, // 0
     0.5f, -0.5f, // 1
     0.5f,  0.5f, // 2
    -0.5f,  0.5f  // 3
};
```

Each vertex has an **index number**:

```
0 ---- 1
|      |
3 ---- 2
```

---

### Step 2 — Indices (EBO)

```cpp
unsigned int indices[] = {
    0, 1, 2,   // first triangle
    2, 3, 0    // second triangle
};
```

This tells OpenGL:

> “Use vertex 0, then 1, then 2 to make a triangle…”

---

# 🔗 How OpenGL Uses the EBO (Internals)

When you call:

```cpp
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

OpenGL does this internally:

```
read index → fetch vertex → process vertex shader
```

Example:

```
index = 2 → vertex = vertices[2]
```

---

# 🧠 IMPORTANT RULE (This trips everyone)

> **EBO is stored inside the VAO**

That’s why this order matters:

```cpp
glBindVertexArray(VAO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
```

And why you **do NOT unbind the EBO** after.

❌ Wrong:

```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // breaks VAO
```

✔ Correct:

```cpp
// leave EBO bound
```

---

# 🔁 Comparison: glDrawArrays vs glDrawElements

| Feature              | glDrawArrays | glDrawElements |
| -------------------- | ------------ | -------------- |
| Uses indices         | ❌            | ✅              |
| Reuses vertices      | ❌            | ✅              |
| Efficient            | ❌            | ✅              |
| Used in real engines | Rare         | Always         |

---

# 🧠 Why GPUs Love EBOs

* Less memory transfer
* Better cache usage
* Faster rendering
* Required for complex meshes

Every real model:

* cubes
* characters
* terrain
  uses **EBOs**

---

# 🧪 Minimal Correct EBO Setup (Template)

```cpp
unsigned int VAO, VBO, EBO;

glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

// VBO
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// EBO
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// attribute
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glBindVertexArray(0);
```

---

# 🧠 Mental Model (memorize this)

> **VBO = data**
> **EBO = order**
> **VAO = remembers everything**

---

# 🚀 Why You Should Always Use EBOs

* Any shape with shared vertices
* Any mesh loaded from file
* Any real OpenGL application

---

If you want next:

* Step-by-step EBO **debug checklist**
* Visual diagram
* Why lines/points still use EBO
* Convert this into a **Chapter-style `.md`**

Just say the word 👍

 */