#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "shader.hpp"
#include <stb/stb_image.h>
#include "TextureManager.hpp"
#include "VertexArrayObject.hpp"
#include "VertexTypes.hpp"
#include "MeshManager.hpp"
#include "Mesh.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Camera.hpp"
#include "Transform.hpp"


unsigned int width = 1920;
unsigned int height = 1080;


Mesh* mesh;
//Mesh* mesh2;
Mesh* mesh3;
Mesh* mesh4;

unsigned int texture; // texture object
unsigned int texture2; // texture object 2
unsigned int texture3; // texture object 3
unsigned int textureCubeMap; // texture object Cube Map

std::vector<std::string> faces{
		"./images/right.jpg",
		"./images/left.jpg",
		"./images/top.jpg",
		"./images/bottom.jpg",
		"./images/front.jpg",
		"./images/back.jpg"
};



int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "My OpenGL Project", /*glfwGetPrimaryMonitor()*/NULL, NULL);
	if (window == NULL) {
		std::cout << "Pencere oluþturulurken bir hata oluþtu!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	/*glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});*/


	texture = TextureManager::getInstance()->loadTexture("./images/brick.jpg");
	texture2 = TextureManager::getInstance()->loadTexture("./images/container.jpg");
	texture3 = TextureManager::getInstance()->loadTexture("./images/brick2.jpg");
	textureCubeMap = TextureManager::getInstance()->loadCubeMapTexture(faces);


	MeshManager* manager = MeshManager::getInstance();
	
	mesh = manager->buildCube();
	//mesh2 = manager->buildSquare(10.0f);
	mesh3 = manager->buildPyramid();
	mesh4 = manager->buildCircle(20.0f, 128);


	Shader shader;
	shader.attachShader("vertexshader.glsl", GL_VERTEX_SHADER);
	shader.attachShader("fragmentshader.glsl", GL_FRAGMENT_SHADER);
	shader.link();
	shader.addUniform("uMatrixProjection");
	shader.addUniform("uMatrixCamera");
	shader.addUniform("uMatrixTransform");

	Shader cubeShader;
	cubeShader.attachShader("cubevertexshader.glsl", GL_VERTEX_SHADER);
	cubeShader.attachShader("cubefragmentshader.glsl", GL_FRAGMENT_SHADER);
	cubeShader.link();
	cubeShader.addUniform("uMatrixProjection");
	cubeShader.addUniform("uMatrixCamera");
	cubeShader.addUniform("uMatrixTransform");


	// Camera Matrix
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 4.0f, 100.0f);

	// Projection Matrix
	camera.setProjection(120.0f, 0.1f, 100.0f);

	// Transform Matrix
	Transform* transform = new Transform();
	glm::mat4 matrixTransform = transform->getMatrix(); // ayarlamama gerek yok default olarak ayarlý constructor da




	glEnable(GL_DEPTH_TEST);

	// Delta Time
	float currentFrame = glfwGetTime();
	float lastFrame = currentFrame;
	float deltaTime;

	// Render
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//std::cout << "FPS: " << (1 / deltaTime) << std::endl;
		camera.updateCameraLookAt();
		camera.inputs(window, deltaTime);








		// CubeShader'ý aktif ediyor - CUBESHADER KISMI
		cubeShader.use();
		cubeShader.setMat4("uMatrixProjection", camera.getProjection());
		cubeShader.setMat4("uMatrixCamera", camera.getCameraLookAt());
		cubeShader.setMat4("uMatrixTransform", &matrixTransform);



		transform->setPosition(camera.getCameraPosition());
		transform->setEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		transform->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
		transform->update();
		matrixTransform = transform->getMatrix();
		
		//cubeShader.setMat4("uMatrixProjection", camera.getProjection());
		//cubeShader.setMat4("uMatrixCamera", camera.getCameraLookAt());
		cubeShader.setMat4("uMatrixTransform", &matrixTransform);
		glDepthMask(GL_FALSE);
		TextureManager::getInstance()->activateCubeMapTexture(textureCubeMap);
		mesh->draw();
		glDepthMask(GL_TRUE);













		// shader'ý aktif ediyor - NORMAL SHADER KISMI
		shader.use();
		shader.setMat4("uMatrixProjection", camera.getProjection());
		shader.setMat4("uMatrixCamera", camera.getCameraLookAt());
		shader.setMat4("uMatrixTransform", &matrixTransform);


		
		//küp
		transform->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		transform->setEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
		transform->update();
		matrixTransform = transform->getMatrix();

		//shader.setMat4("uMatrixProjection", camera.getProjection());
		//shader.setMat4("uMatrixCamera", camera.getCameraLookAt());
		shader.setMat4("uMatrixTransform", &matrixTransform);
		TextureManager::getInstance()->activateTexture(GL_TEXTURE0, texture2);
		mesh->draw();




		//kare
		// TextureManager::getInstance()->activateTexture(GL_TEXTURE0, texture?);
		// mesh2->draw();
		



		//piramid
		transform->setPosition(glm::vec3(2.0f, -0.5f, 0.0f));
		transform->setEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
		transform->update();
		matrixTransform = transform->getMatrix();

		//shader.setMat4("uMatrixProjection", camera.getProjection());
		//shader.setMat4("uMatrixCamera", camera.getCameraLookAt());
		shader.setMat4("uMatrixTransform", &matrixTransform);
		TextureManager::getInstance()->activateTexture(GL_TEXTURE0, texture3);
		mesh3->draw();



		//daire
		transform->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		transform->setEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		transform->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
		transform->update();
		matrixTransform = transform->getMatrix();
		
		//shader.setMat4("uMatrixProjection", camera.getProjection());
		//shader.setMat4("uMatrixCamera", camera.getCameraLookAt());
		shader.setMat4("uMatrixTransform", &matrixTransform);
		TextureManager::getInstance()->activateTexture(GL_TEXTURE0, texture);
		mesh4->draw();
		



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	mesh->deleteBuffers();
	//mesh2->deleteBuffers();
	mesh3->deleteBuffers();
	mesh4->deleteBuffers();
	TextureManager::getInstance()->deleteTexture(texture);
	TextureManager::getInstance()->deleteTexture(texture2);
	TextureManager::getInstance()->deleteTexture(textureCubeMap);
	shader.~Shader();
	cubeShader.~Shader();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
};