#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP
#include "VertexTypes.hpp"

class VertexArrayObject {
public:
	VertexArrayObject();
	void build(const Vertex3DTextureList& vertices, const IndexList& indices);
	void activate();
	void deactivate();
	int getVertexCount();
	int getIndexCount();
	~VertexArrayObject();
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	std::vector<unsigned int> attribList;
	unsigned int vertexCount;
	unsigned int indexCount;
};

#endif // !VERTEXARRAYOBJECT_HPP