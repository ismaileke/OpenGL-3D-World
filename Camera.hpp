#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
	Camera(unsigned int width, unsigned int height, glm::vec3 cameraPosition, float speed, float sensivity);
	void inputs(GLFWwindow* window, float deltaTime);
	void setProjection(float FOVdegree, float nearPlane, float farPlane);
	void updateCameraLookAt();
	glm::mat4 setTransform(glm::vec3 objectPos, float rotateAngle, glm::vec3 rotateDirection, glm::vec3 objectScale, bool isCube);
	glm::mat4* getProjection();
	glm::mat4* getCameraLookAt();
	glm::vec3 getCameraPosition();
private:
	// Camera
	glm::vec3 camPos;
	glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Orientation
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);

	unsigned int width;
	unsigned int height;

	bool firstClick = true;
	float speed;
	float sensivity;

	glm::mat4 matrixProjection;
	glm::mat4 matrixCamera;
};
#endif // !CAMERA_HPP
