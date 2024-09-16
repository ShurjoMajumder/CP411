#version 310

layout (location = 0) in vec4 color;
out vec4 fColor;

void main() 
{ 
    fColor = color;
} 

