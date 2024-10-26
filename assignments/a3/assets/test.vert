#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 i_vertexColor;

uniform mat4x4 M;
uniform mat4x4 PV;

out vec4 vertexColor;

void main() {
    gl_Position = PV * M * vec4(position, 1.0);
    vertexColor = i_vertexColor;
}
