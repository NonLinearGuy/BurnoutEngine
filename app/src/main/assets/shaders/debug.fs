#version 300 es

out vec4 finalColor;
in vec2 TexCoords;
flat in vec4 col;


void main()
{
float inner_radius = 0.46f;
float outer_radius = 0.47f;

vec4 color = col;
    vec4 alpha0 = vec4(0.0f);
    float dx = .5f - TexCoords.x;
    float dy = .5f - TexCoords.y;
    float dist = sqrt((dx*dx) + (dy*dy));
    finalColor = mix(color,alpha0,smoothstep(inner_radius,outer_radius,dist));
}