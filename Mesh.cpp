#include "Mesh.hpp"
#include "VertexArrayObject.hpp"
#include <glad/glad.h>

void Mesh::draw() {
	vao->activate();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	vao->deactivate();
}

void Mesh::deleteBuffers() {
	vao->~VertexArrayObject();
}
