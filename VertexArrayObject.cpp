#include "VertexArrayObject.hpp"
#include "VertexTypes.hpp"
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject() {
	VAO = 0;
	VBO = 0;
	EBO = 0;
	vertexCount = 0;
	indexCount = 0;
	attribList;
}
VertexArrayObject::~VertexArrayObject() {
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void VertexArrayObject::build(const Vertex3DTextureList& vertices, const IndexList& indices) {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	

	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex3DTexture) * vertices.size()), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(unsigned int) * indices.size()), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	attribList.push_back(0);
	attribList.push_back(1);

	vertexCount = vertices.size();
	indexCount = indices.size();
}

void VertexArrayObject::activate() {
	glBindVertexArray(VAO);
	for (auto next : attribList) {
		glEnableVertexAttribArray(next);
	}
}

void VertexArrayObject::deactivate() {
	for (auto next : attribList) {
		glDisableVertexAttribArray(next);
	}
	glBindVertexArray(0);
}

int VertexArrayObject::getVertexCount() {
	return vertexCount;
}

int VertexArrayObject::getIndexCount() {
	return indexCount;
}
