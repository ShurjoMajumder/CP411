#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 i_fillColor;
layout (location = 2) in vec4 i_strokeColor;

out vec4 fillColor;
out vec4 strokeColor;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    fillColor = i_fillColor;
    strokeColor = i_strokeColor;
}
