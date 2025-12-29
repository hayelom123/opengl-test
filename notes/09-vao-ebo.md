# Chapter 9: VAO + EBO (Indexed Rendering)

This chapter introduces **Vertex Array Objects (VAO)** and **Element Buffer Objects (EBO)**.
These two objects help OpenGL organize vertex data and reuse vertices efficiently
when drawing shapes.

The main idea is simple:

- **VBO** stores vertex data
- **EBO** stores indices (which vertices to draw)
- **VAO** remembers how everything is connected

Using VAO and EBO together makes rendering faster, cleaner, and scalable.

---

## Basic Idea (Very Easy Explanation)

When drawing shapes like rectangles or complex objects, many vertices are reused.
Instead of duplicating vertex data, OpenGL allows us to reuse vertices by referencing
them with indices.

- VAO = configuration memory
- VBO = vertex data
- EBO = index data

---

## Key Steps

1. Initialize GLFW and create an OpenGL context
2. Load OpenGL function pointers using GLAD
3. Define vertex data (positions)
4. Define index data
5. Create and bind a VAO
6. Create and bind a VBO
7. Create and bind an EBO
8. Configure vertex attributes
9. Draw using `glDrawElements`
10. Clean up resources

---

## Source Code

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "VAO + EBO", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex data (4 vertices)
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    // Index data (2 triangles)
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAO, VBO, EBO;

    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
```

Great question. I’ll explain **Element Buffer Objects (EBOs)** from **zero**, slowly, clearly, and **without assuming any prior knowledge**.

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

- Vertex **A** is used **twice**
- Vertex **C** is used **twice**

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
| Uses indices         | ❌           | ✅             |
| Reuses vertices      | ❌           | ✅             |
| Efficient            | ❌           | ✅             |
| Used in real engines | Rare         | Always         |

---

# 🧠 Why GPUs Love EBOs

- Less memory transfer
- Better cache usage
- Faster rendering
- Required for complex meshes

Every real model:

- cubes
- characters
- terrain
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

> **VBO = data** > **EBO = order** > **VAO = remembers everything**

---

# 🚀 Why You Should Always Use EBOs

- Any shape with shared vertices
- Any mesh loaded from file
- Any real OpenGL application

Nice — **VAO** is the missing puzzle piece.
I’ll explain it **slowly, visually, and correctly**, the same way OpenGL actually works.

No assumptions. Beginner-friendly. Real mental model.

---

# 🧠 What Problem VAO Solves

Before VAOs existed, every frame you had to do this:

```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glVertexAttribPointer(...);
glEnableVertexAttribArray(...);
```

❌ Repeating this **every draw call**
❌ Easy to mess up
❌ Slow

---

# ✅ What a VAO Really Is

> **VAO = a container that remembers how vertex data is laid out**

It does **NOT** store vertex data.
It stores **instructions**:

- Which VBO to use
- Which EBO to use
- How attributes are read

---

# 📦 What a VAO Stores (Exactly)

When a VAO is bound, OpenGL records:

✔ Vertex attribute format (`glVertexAttribPointer`)
✔ Which VBO each attribute uses
✔ Which attributes are enabled
✔ The **EBO binding**

❌ NOT vertex data
❌ NOT shader programs

---

# 🧠 Think of VAO Like This

### Without VAO

> “Every time I draw, I must explain everything again.”

### With VAO

> “I explain once. Then just say: draw.”

---

# 🔗 VAO + VBO + EBO Relationship

```
VAO
 ├── Attribute 0 → VBO (positions)
 ├── Attribute 1 → VBO (colors)
 └── EBO (indices)
```

When you bind the VAO, **all of this is restored automatically**.

---

# 🧪 Minimal VAO Setup (Correct Order Matters!)

```cpp
unsigned int VAO, VBO, EBO;

glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

// VBO
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// EBO (stored inside VAO!)
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// Attribute layout
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// Done configuring
glBindVertexArray(0);
```

---

# ⚠️ MOST COMMON VAO MISTAKE (Important)

❌ This breaks rendering:

```cpp
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
```

Why?

> Because **EBO binding belongs to the VAO**

Once you unbind it, the VAO forgets indices.

✔ Correct: **do NOT unbind EBO**

---

# 🧠 What Happens During Rendering

At draw time, your code becomes **very simple**:

```cpp
glUseProgram(shader);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
```

OpenGL internally:

1. Restores attribute layout
2. Binds correct VBOs
3. Uses correct EBO
4. Draws geometry

---

# 🧠 Analogy (Best One)

### VAO is like a **recipe card**

- VBO = ingredients
- EBO = cooking order
- VAO = recipe

You don’t rewrite the recipe every time — you just cook.

---

# 📊 Comparison Summary

| Object | Purpose              |
| ------ | -------------------- |
| VBO    | Stores vertex data   |
| EBO    | Stores indices       |
| VAO    | Stores configuration |

---

# 🔁 Multiple Objects Example

```cpp
glBindVertexArray(VAO_triangle);
glDrawElements(...);

glBindVertexArray(VAO_square);
glDrawElements(...);
```

No reconfiguration needed.

---

# 🧠 Golden Rule (memorize)

> **Bind VAO → configure buffers → unbind VAO**

---

# 🚀 Why VAOs Are Mandatory in Core Profile

OpenGL **core profile WILL NOT draw without a VAO**.

If you forget:

```cpp
glBindVertexArray(VAO);
```

→ black screen.

---
