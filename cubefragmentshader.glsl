#version 330 core
out vec4 fragColor;

uniform samplerCube ourTexture;

in vec3 textureCoord;

void main() {
	fragColor = texture(ourTexture, textureCoord);
}