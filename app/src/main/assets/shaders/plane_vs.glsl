#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 projection;

out vec2 texCoords;

void main()
{
    gl_Position = projection * model * vec4(pos,1.0f);
    texCoords = tex;
}