#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 offset;
layout(location = 2) in vec4 color;
layout(location = 3) in vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 frameSize;

out vec2 TexCoords;

void main()
{

vec2 texCoords[] = vec2[](
		vec2(tex.x,tex.y),
		vec2(tex.x + frameSize.x,tex.y),
		vec2(tex.x + frameSize.x, tex.y + frameSize.y),
		vec2(tex.x,tex.y + frameSize.y)
	);

	TexCoords = texCoords[gl_VertexID];
    vec4 position = vec4(pos,1.0f);
	position.xy *= vec2(offset.w); //scaling first
	position.xyz += offset.xyz; //then translating

    gl_Position = projection * view  * position;
}