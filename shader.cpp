#include "shader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <map>

Shader::Shader() {
	programId = glCreateProgram();
}

Shader::~Shader() {
	glDeleteProgram(programId);
}

void Shader::attachShader(const char* fileName, unsigned int shaderType) {
	unsigned int shaderId = glCreateShader(shaderType);
	std::string sourceCode = getShaderFromFile(fileName);
	const char* chSourceCode = &sourceCode[0];
	glShaderSource(shaderId, 1, &chSourceCode, NULL);
	glCompileShader(shaderId);
	glAttachShader(programId, shaderId);
	glDeleteShader(shaderId);
}

void Shader::link() const {
	glLinkProgram(programId);
}

void Shader::use() const {
	glUseProgram(programId);
}

void Shader::addUniform(const std::string& varName) {
	uniformData[varName] = glGetUniformLocation(programId, varName.c_str());
}

void Shader::setVec3(const std::string& varName, const glm::vec3& value) {
	glUniform3f(uniformData[varName], value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& varName, const glm::vec4& value) {
	glUniform4f(uniformData[varName], value.r, value.g, value.b, value.a);
}

void Shader::setMat3(const std::string& varName, const glm::mat3* value) {
	glUniformMatrix3fv(uniformData[varName], 1, false, (GLfloat*)value);
}

void Shader::setMat4(const std::string& varName, const glm::mat4* value) {
	glUniformMatrix4fv(uniformData[varName], 1, false, (GLfloat*)value);
}

std::string Shader::getShaderFromFile(const char* fileName) {
	std::ifstream file(fileName);
	std::string data;

	if (file.is_open()) {
		char readChar;
		while ((readChar = file.get())!=EOF) {
			data += readChar;
		}
		file.close();
	}

	return data;

}
