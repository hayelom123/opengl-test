#version 330 core
layout(location=0) in vec3 aPos;

out vec4 outColor;// specify a color output to the fragment shader

void main(){
    gl_Position = vec4(aPos, 1.0);

    outColor = vec4(aPos, 1.0f);
     
}