#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include <glm/mat4x4.hpp>

class Transform
{
public:
	Transform();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec3 getEulerAngles();
	glm::mat4 getMatrix();

	void setPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
	void setEulerAngles(const glm::vec3& eulerAngles);
	void update();

protected:
	glm::mat4 objTransform;

	glm::vec3 objPosition;
	glm::vec3 objScale;
	glm::vec3 objEulerAngles;
};


#endif // !TRANSFORM_HPP
