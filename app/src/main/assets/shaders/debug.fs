#version 300 es

out vec4 finalColor;
in vec2 TexCoords;

uniform sampler2D atlas;

void main()
{
    finalColor = texture(atlas,TexCoords);
}