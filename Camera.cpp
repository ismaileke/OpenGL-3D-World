#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(unsigned int width, unsigned int height, glm::vec3 cameraPosition, float speed, float sensivity) {
	//Camera::matrixCamera = glm::mat4(1.0f);
	//Camera::matrixProjection = glm::mat4(1.0f);
	Camera::width = width;
	Camera::height = height;
	camPos = cameraPosition;
	Camera::speed = speed;
	Camera::sensivity = sensivity;
}

void Camera::inputs(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camPos += speed * orientation * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camPos += speed * -glm::normalize(glm::cross(orientation, camUp)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camPos += speed * -orientation * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camPos += speed * glm::normalize(glm::cross(orientation, camUp)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camPos += speed * camUp * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camPos += speed * -camUp * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 8.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 4.0f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClick) {
			glfwSetCursorPos(window, (width / static_cast<double>(2)), (height / static_cast<double>(2)));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, camUp)));

		if (abs(glm::angle(newOrientation, camUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		orientation = glm::rotate(orientation, glm::radians(-rotY), camUp);

		glfwSetCursorPos(window, (width / static_cast<double>(2)), (height / static_cast<double>(2)));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

glm::mat4 Camera::setTransform(glm::vec3 objectPos, float rotateAngle, glm::vec3 rotateDirection, glm::vec3 objectScale, bool isCube) {
	// object position
	glm::mat4 matrixTranslation = glm::mat4(1);
	if (isCube) {
		matrixTranslation = glm::translate(glm::mat4(1), camPos);
	}
	else {
		matrixTranslation = glm::translate(glm::mat4(1), objectPos);
	}
	
	// object rotation                                      açý                     hangi yönde döneceði
	glm::mat4 matrixRotation = glm::rotate(glm::mat4(1), glm::radians(rotateAngle), rotateDirection);
	// object scale
	glm::mat4 matrixScale = glm::scale(glm::mat4(1), objectScale);
	// transform matrix
	return matrixTranslation * matrixRotation * matrixScale;
}

void Camera::setProjection(float FOVdegree, float nearPlane, float farPlane) {
	matrixProjection = glm::perspective(glm::radians(FOVdegree), ((float)width / (float)height), nearPlane, farPlane);
}

void Camera::updateCameraLookAt() {
	matrixCamera = glm::lookAt(camPos, camPos + orientation, camUp);
}

glm::mat4* Camera::getProjection() {
	return &matrixProjection;
}

glm::mat4* Camera::getCameraLookAt() {
	return &matrixCamera;
}

glm::vec3 Camera::getCameraPosition() {
	return camPos;
}