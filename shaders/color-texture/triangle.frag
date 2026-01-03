#version 330 core
 
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D ourTexture;

void main()
{
FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
//To get a little funky we can also mix the resulting texture color with the vertex colors. 
//We simply multiply the resulting texture color with the vertex color in the fragment shader to mix both colors:

  
}