#ifndef MESH_HPP
#define MESH_HPP
#include "VertexTypes.hpp"

class VertexArrayObject;
class MeshManager;

class Mesh {
public:
	void draw();
	void deleteBuffers();
private:
	VertexArrayObject* vao;
	unsigned int vertexCount;
	unsigned int indexCount;

	friend MeshManager;
};

#endif // !MESH_HPP