#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 offset;
layout(location = 2) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;
flat out vec4 col;


void main()
{

vec2 texCoords[] = vec2[](
		vec2(0.0f),
		vec2(1.0f,0.0f),
		vec2(1.0f),
		vec2(0.0f,1.0f)
	);

	TexCoords = texCoords[gl_VertexID];
    col = color;
    vec4 position = vec4(pos,1.0f);
	position.xy *= vec2(offset.w); //scaling first
	position.xyz += offset.xyz; //then translating

    gl_Position = projection * view * model * position;
}