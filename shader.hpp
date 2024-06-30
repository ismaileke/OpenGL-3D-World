#define SHADER_HPP
#ifdef SHADER_HPP
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <map>
#include <glm/mat3x3.hpp>

class Shader {
public:
	Shader();
	~Shader();
	void attachShader(const char* fileName, unsigned int shaderType);
	void link() const;
	void use() const;
	void addUniform(const std::string& varName);
	void setVec3(const std::string& varName, const glm::vec3& value);
	void setVec4(const std::string& varName, const glm::vec4& value);
	void setMat3(const std::string& varName, const glm::mat3* value);
	void setMat4(const std::string& varName, const glm::mat4* value);
private:
	unsigned int programId;
	std::string getShaderFromFile(const char* fileName);

	std::map<std::string, unsigned int> uniformData;
};

#endif
