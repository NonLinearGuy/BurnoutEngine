#version 300 es

out vec4 finalColor;
in vec2 TexCoords;
flat in int texUnit;
in float alpha;

uniform sampler2D fire;
uniform sampler2D smoke;

void main()
{
    if(texUnit == 0)
        finalColor = texture(fire,TexCoords);
    else
        finalColor = texture(smoke,TexCoords);
}