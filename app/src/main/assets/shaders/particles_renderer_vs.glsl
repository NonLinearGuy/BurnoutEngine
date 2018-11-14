#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec4 col;
layout(location = 3) in vec3 offset;
layout(location = 4) in vec3 scaler;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex_coords;
out vec4 color;

void main()
{
	tex_coords = tex;
	color = col;

	vec4 position = vec4(pos,1.0f);
	position.xyz *= scaler; //scaling first
	position.xyz += offset; //then translating
	
	gl_Position = projection*view*position;

}