#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 mat;
out vec3 fCol;

void main()
{
    fCol = aCol;
    gl_Position = mat*vec4( aPos , 1.0);
}