#version 330 core
out vec4 fragColor;

uniform sampler2D ourTexture;

in vec2 textureCoord;

void main() {
	fragColor = texture(ourTexture, textureCoord) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}