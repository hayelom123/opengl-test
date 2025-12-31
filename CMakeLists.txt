cmake_minimum_required(VERSION 3.16)
project(MyOpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# GLAD
include_directories(include)

# GLFW (brew path)
set(GLFW_DIR "/opt/homebrew/opt/glfw") # Intel Macs: "/usr/local/opt/glfw"
include_directories(${GLFW_DIR}/include)
link_directories(${GLFW_DIR}/lib)

# GLM
set(GLM_DIR "/opt/homebrew/opt/glm") # Intel Macs: "/usr/local/opt/glm"
include_directories(${GLM_DIR}/include) 
 


# Source files
set(SOURCES src/main.cpp src/utils.cpp src/glad.c)

# Find OpenGL
find_library(OpenGL_LIBRARY OpenGL)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARY} glfw)
