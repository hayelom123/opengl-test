#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D checkerTex;// ourTexture;

void main(){
    FragColor=texture(checkerTex,TexCoord);
}