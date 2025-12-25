#version 330 core
layout(location = 0) in vec4 position;
out vec4 vertexColor;
void main()
{
    gl_Position = position;
    vertexColor = vec4(1.0, 0.5, 0.2, 1.0);
}