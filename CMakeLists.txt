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
 
# # Copy container.jpg to the binary directory after each build
# configure_file(${CMAKE_SOURCE_DIR}/textures/container.jpg ${CMAKE_BINARY_DIR}/container.jpg COPYONLY)

# Create textures directory in build
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/textures")

# Copy all files from source textures/ to build/textures/, preserving subfolders
file(GLOB_RECURSE TEXTURE_FILES "${CMAKE_SOURCE_DIR}/textures/*")

foreach(TEXTURE_FILE ${TEXTURE_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/textures" "${TEXTURE_FILE}")
    configure_file("${TEXTURE_FILE}" "${CMAKE_BINARY_DIR}/textures/${REL_PATH}" COPYONLY)
endforeach()



# Source files
set(SOURCES src/main.cpp src/utils.cpp src/glad.c src/stb_image.cpp)

# Find OpenGL
find_library(OpenGL_LIBRARY OpenGL)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARY} glfw)
