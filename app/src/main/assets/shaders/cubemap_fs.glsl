#version 300 es

in vec3 sampleDir;
uniform samplerCube cubemap;
out vec4 finalColor;

void main() {
    finalColor = texture(cubemap,sampleDir);
}

