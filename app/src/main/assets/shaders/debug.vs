#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec4 scaleAlphaTexUnit;
layout(location = 3) in vec3 offset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 frameSize;


out vec2 TexCoords;
flat out int texUnit;
out float alpha;

void main()
{

vec2 texCoords[] = vec2[](
		vec2(tex.x,tex.y),
		vec2(tex.x+frameSize.x,tex.y),
		vec2(tex.x+frameSize.x,tex.y+frameSize.y),
		vec2(tex.x,tex.y+frameSize.y)
	);

	TexCoords = texCoords[gl_VertexID];
    int unit = int(scaleAlphaTexUnit.w);
    texUnit = unit;
    alpha = scaleAlphaTexUnit.z;

    vec4 position = vec4(pos,1.0f);
	position.xy *= scaleAlphaTexUnit.xy; //scaling first
	//position.xy *= scaleRotation.zw; //rotation
	position.xyz += offset; //then translating

    gl_Position = projection * view * model * position;
}