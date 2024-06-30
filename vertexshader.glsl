#version 330 core
layout (location=0) in vec3 inPosition;
layout (location=1) in vec2 inTextureCoord;

uniform mat4 uMatrixProjection;
uniform mat4 uMatrixCamera;
uniform mat4 uMatrixTransform;

out vec2 textureCoord;


void main() {
	gl_Position = uMatrixProjection * uMatrixCamera * uMatrixTransform * vec4(inPosition, 1.0);
	textureCoord = inTextureCoord;
}