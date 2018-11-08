#version 300 es

layout(location = 0) in vec3 pos;

out vec3 sampleDir;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * mat4(mat3(view)) * vec4(pos,1.0f);
    sampleDir = pos;
}