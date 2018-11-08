#version 300 es

uniform vec3 color;

out vec4 finalColor;
in vec2 texCoords;

uniform sampler2D sampler0;

void main()
{
    finalColor = texture(sampler0,texCoords);
}