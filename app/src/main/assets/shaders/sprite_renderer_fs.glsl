#version 300 es

in vec2 texCoords;

uniform sampler2D sampler0;
uniform vec4 color;
uniform bool use_color;

out vec4 finalColor;

void main()
{  
	finalColor = vec4(1.0f);
}