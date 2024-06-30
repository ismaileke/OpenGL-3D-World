#include "Transform.hpp"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform() {
	objPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	objScale = glm::vec3(1.0f, 1.0f, 1.0f);
	objEulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Transform::getPosition() {
	return objPosition;
}

glm::vec3 Transform::getScale() {
	return objScale;
}

glm::vec3 Transform::getEulerAngles() {
	return objEulerAngles;
}

glm::mat4 Transform::getMatrix() {
	return objTransform;
}

void Transform::setPosition(const glm::vec3& position) {
	objPosition = position;
}

void Transform::setScale(const glm::vec3& scale) {
	objScale = scale;
}

void Transform::setEulerAngles(const glm::vec3& eulerAngles) {
	objEulerAngles = eulerAngles;
}

void Transform::update() {
	glm::mat4 mtxTranslate = glm::translate(glm::mat4(1), objPosition);
	glm::mat4 mtxScale = glm::scale(glm::mat4(1), objScale);

	glm::mat4 mtxRotX, mtxRotY, mtxRotZ;

	mtxRotX = glm::rotate(glm::mat4(1), glm::radians(objEulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
	mtxRotY = glm::rotate(glm::mat4(1), glm::radians(objEulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
	mtxRotZ = glm::rotate(glm::mat4(1), glm::radians(objEulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));

	objTransform = mtxTranslate * (mtxRotZ * mtxRotY * mtxRotX) * mtxScale;
}
