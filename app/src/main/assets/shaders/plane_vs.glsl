#version 300 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec3 uLightPosition;

out mat3 TBN;
out vec2 texCoords;
out vec3 fragPos;
out vec3 lightPosition;
void main()
{

vec3 tangent = vec3(1.0f,0.0f,0.0f);
vec3 bitangent = vec3(0.0f,1.0f,0.0f);
vec3 normal = vec3(0.0f,0.0f,1.0f);


    vec4 viewPos = view * model * vec4(pos,1.0f);
    gl_Position = projection * viewPos;
    fragPos = viewPos.xyz;
    texCoords = tex;
    vec3 T = normalize(vec3(view * model * vec4(tangent,   0.0)));
    vec3 B = normalize(vec3(view * model * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3( view * model * vec4(normal,    0.0)));
    TBN = mat3(T, B, N);
    lightPosition = vec3(view * vec4(uLightPosition,1.0f));
}