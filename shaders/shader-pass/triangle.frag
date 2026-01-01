#version 330 core
out vec4 FragColor;

in vec4 outColor;// the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = outColor;
    // vec4(0.0f, 1.0f, 0.0f, 1.0f);

}