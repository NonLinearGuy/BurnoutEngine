#version 300 es

out vec4 finalColor;

in vec2 texCoords;
in vec3 fragPos;

in mat3 TBN;
in vec3 lightPosition;

uniform sampler2D grass0;
uniform sampler2D path1;
uniform sampler2D blendFactor2;
uniform sampler2D normalMap3;

uniform vec3 lightColor;

uniform float constant;
uniform float linear;
uniform float quadratic;

float tileSize = 4.0f;

void main()
{
    vec4 grassColor = texture(grass0,texCoords * tileSize);
    vec4 pathColor = texture(path1,texCoords * tileSize);
    float blendFactor = texture(blendFactor2,texCoords * tileSize).r;
    vec4 color = ((1.0 - blendFactor) * pathColor) + (blendFactor * grassColor);

    vec3 normal = texture(normalMap3,texCoords * tileSize).rgb;
    normal = normalize(normal*2.0 - 1.0);
    normal = normalize(TBN * normal);
    vec3 lightDir = normalize(lightPosition - fragPos);

    float global =  0.05;
    float diffuse = max(dot(normal,lightDir),0.0);

    float distance = length(lightPosition - fragPos);
    float attenuation = 1.0 / (constant + linear * distance +
        		    quadratic * (distance * distance));

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = normalize(reflect(-lightDir,normal));
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);


    //lightIntensity *= attenuation;
  //   global *= attenuation;
   //  diffuse *= attenuation;
    // specular *= attenuation;

    finalColor = color * (global + diffuse + specular);
}