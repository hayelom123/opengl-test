#version 330 core
 
/*
Uniforms

Uniforms are another way to pass data from our application on the CPU to the shaders on the GPU. 
Uniforms are however slightly different compared to vertex attributes. 
First of all, uniforms are global. 
Global, meaning that a uniform variable is unique per shader program object, and can be accessed from any shader at any stage in the shader program.
Second, whatever you set the uniform value to, uniforms will keep their values until they're either reset or updated.
*/

out vec4 FragColor;
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main(){
    FragColor = ourColor;
}    
/*
If you declare a uniform that isn't used anywhere in your GLSL code the compiler will silently remove the variable from the compiled version which is the cause for several frustrating errors; keep this in mind!
*/