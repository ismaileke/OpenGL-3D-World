#include "MeshManager.hpp"
#include "VertexTypes.hpp"
#include "VertexArrayObject.hpp"
#include "Mesh.hpp"
#include <glad/glad.h>
#include <glm/trigonometric.hpp>

MeshManager* MeshManager::m_Instance = 0;

MeshManager::MeshManager() {

}

MeshManager* MeshManager::getInstance()
{
    if (m_Instance) {
        return m_Instance;
    }
    m_Instance = new MeshManager();
    return m_Instance;
}

Mesh* MeshManager::buildCube() {
	
	if (!VAOMap.count("cubeTex")) {
		Vertex3DTextureList vertices;
		IndexList indices;

		float length = 1.0f;
		glm::vec3 v[8];
		v[0] = glm::vec3(-length / 2, -length / 2, -length / 2);
		v[1] = glm::vec3(length / 2, -length / 2, -length / 2);
		v[2] = glm::vec3(length / 2, -length / 2, length / 2);
		v[3] = glm::vec3(-length / 2, -length / 2, length / 2);
		v[4] = glm::vec3(-length / 2, length / 2, -length / 2);
		v[5] = glm::vec3(length / 2, length / 2, -length / 2);
		v[6] = glm::vec3(length / 2, length / 2, length / 2);
		v[7] = glm::vec3(-length / 2, length / 2, length / 2);

		Vertex3DTexture tempVertices[24];

		tempVertices[0].position = v[7];
		tempVertices[1].position = v[3];
		tempVertices[2].position = v[2];
		tempVertices[3].position = v[6];
		tempVertices[0].texture = glm::vec2(0.0f, 1.0f);
		tempVertices[1].texture = glm::vec2(0.0f, 0.0f);
		tempVertices[2].texture = glm::vec2(1.0f, 0.0f);
		tempVertices[3].texture = glm::vec2(1.0f, 1.0f);

		tempVertices[4].position = v[6];
		tempVertices[5].position = v[2];
		tempVertices[6].position = v[1];
		tempVertices[7].position = v[5];
		tempVertices[4].texture = glm::vec2(0.0f, 1.0f);
		tempVertices[5].texture = glm::vec2(0.0f, 0.0f);
		tempVertices[6].texture = glm::vec2(1.0f, 0.0f);
		tempVertices[7].texture = glm::vec2(1.0f, 1.0f);


		tempVertices[8].position = v[4];
		tempVertices[9].position = v[7];
		tempVertices[10].position = v[6];
		tempVertices[11].position = v[5];
		tempVertices[8].texture = glm::vec2(0.0f, 1.0f);
		tempVertices[9].texture = glm::vec2(0.0f, 0.0f);
		tempVertices[10].texture = glm::vec2(1.0f, 0.0f);
		tempVertices[11].texture = glm::vec2(1.0f, 1.0f);

		tempVertices[12].position = v[0];
		tempVertices[13].position = v[3];
		tempVertices[14].position = v[2];
		tempVertices[15].position = v[1];
		tempVertices[12].texture = glm::vec2(0.0f, 1.0f);
		tempVertices[13].texture = glm::vec2(0.0f, 0.0f);
		tempVertices[14].texture = glm::vec2(1.0f, 0.0f);
		tempVertices[15].texture = glm::vec2(1.0f, 1.0f);

		tempVertices[16].position = v[4];
		tempVertices[17].position = v[0];
		tempVertices[18].position = v[1];
		tempVertices[19].position = v[5];
		tempVertices[16].texture = glm::vec2(0.0f, 1.0f);
		tempVertices[17].texture = glm::vec2(0.0f, 0.0f);
		tempVertices[18].texture = glm::vec2(1.0f, 0.0f);
		tempVertices[19].texture = glm::vec2(1.0f, 1.0f);

		tempVertices[20].position = v[7];
		tempVertices[21].position = v[3];
		tempVertices[22].position = v[0];
		tempVertices[23].position = v[4];
		tempVertices[20].texture = glm::vec2(0.0f, 1.0f);
		tempVertices[21].texture = glm::vec2(0.0f, 0.0f);
		tempVertices[22].texture = glm::vec2(1.0f, 0.0f);
		tempVertices[23].texture = glm::vec2(1.0f, 1.0f);

		for (int i = 0; i < 24; i++) {
			vertices.push_back(tempVertices[i]);
		}

		for (int i = 0; i < 6; i++) {
			int startIndex = 4 * i;
			indices.push_back(startIndex);
			indices.push_back(startIndex + 1);
			indices.push_back(startIndex + 2);

			indices.push_back(startIndex);
			indices.push_back(startIndex + 2);
			indices.push_back(startIndex + 3);
		}
		VertexArrayObject* vao = new VertexArrayObject();
		vao->build(vertices, indices);
		// kaplamalý küp
		VAOMap["cubeTex"] = vao;
	}
	
	Mesh* mesh = new Mesh();
	mesh->vao = VAOMap["cubeTex"];
	mesh->vertexCount = VAOMap["cubeTex"]->getVertexCount();
	mesh->indexCount = VAOMap["cubeTex"]->getIndexCount();
	
	return mesh;
}

Mesh* MeshManager::buildSquare(float length) {
	if (!VAOMap.count("squareTex")) {
		Vertex3DTextureList vertices;
		IndexList indices;
		Vertex3DTexture v0, v1, v2, v3;

		//v0.position = glm::vec3(-length / 2, length / 2, 0.0f);
		//v1.position = glm::vec3(-length / 2, -length / 2, 0.0f);
		//v2.position = glm::vec3(length / 2, -length / 2, 0.0f);
		//v3.position = glm::vec3(length / 2, length / 2, 0.0f);
		// 
		//yatay kare
		v0.position = glm::vec3(-length / 2, -0.51f, length / 2);
		v1.position = glm::vec3(-length / 2, -0.51f, -length / 2);
		v2.position = glm::vec3(length / 2, -0.51f, -length / 2);
		v3.position = glm::vec3(length / 2, -0.51f, length / 2);

		v0.texture = glm::vec2(0.0f, 1.0f);
		v1.texture = glm::vec2(0.0f, 0.0f);
		v2.texture = glm::vec2(1.0f, 0.0f);
		v3.texture = glm::vec2(1.0f, 1.0f);

		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(3);

		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		VertexArrayObject* vao = new VertexArrayObject();
		vao->build(vertices, indices);
		// kaplamalý kare
		VAOMap["squareTex"] = vao;
	}

	Mesh* mesh = new Mesh();
	mesh->vao = VAOMap["squareTex"];
	mesh->vertexCount = VAOMap["squareTex"]->getVertexCount();
	mesh->indexCount = VAOMap["squareTex"]->getIndexCount();

	return mesh;
}

Mesh* MeshManager::buildPyramid() {
	if (!VAOMap.count("pyramidTex")) {
		Vertex3DTextureList vertices;
		IndexList indices;
		GLuint indices2[] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4
		};
		Vertex3DTexture v0, v1, v2, v3, v4;
		v0.position = glm::vec3(-0.5f, 0.0f, 0.5f);
		v0.texture = glm::vec2(0.0f, 0.0f);

		v1.position = glm::vec3(-0.5f, 0.0f, -0.5f);
		v1.texture = glm::vec2(5.0f, 0.0f);

		v2.position = glm::vec3(0.5f, 0.0f, -0.5f);
		v2.texture = glm::vec2(0.0f, 0.0f);

		v3.position = glm::vec3(0.5f, 0.0f, 0.5f);
		v3.texture = glm::vec2(5.0f, 0.0f);

		v4.position = glm::vec3(0.0f, 1.0f, 0.0f);
		v4.texture = glm::vec2(2.5f, 5.0f);

		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);

		for (int i = 0; i < 18; i++) {
			indices.push_back(indices2[i]);
		}
		VertexArrayObject* vao = new VertexArrayObject();
		vao->build(vertices, indices);
		// kaplamalý piramit
		VAOMap["pyramidTex"] = vao;
	}

	Mesh* mesh = new Mesh();
	mesh->vao = VAOMap["pyramidTex"];
	mesh->vertexCount = VAOMap["pyramidTex"]->getVertexCount();
	mesh->indexCount = VAOMap["pyramidTex"]->getIndexCount();

	return mesh;
}

Mesh* MeshManager::buildCircle(float radius, int vertexCount) {
	if (!VAOMap.count("circleTex")) {
		Vertex3DTextureList vertices;
		IndexList indices;
		float cAngle = 360.0f / vertexCount;
		int triangleCount = vertexCount - 2;

		for (int i = 0; i < vertexCount; i++) {
			float newAngle = cAngle * i;

			float x = radius * cos(glm::radians(newAngle));
			float y = -0.51f;
			float z = radius * sin(glm::radians(newAngle));
			//float x = radius * cos(glm::radians(newAngle));
			//float y = -1.1f;
			//float z = radius * sin(glm::radians(newAngle));


			Vertex3DTexture vertex;
			vertex.position = glm::vec3(x, y, z);
			vertex.texture = glm::vec2(x, z);///////////////////////////////////////////////////////////////
			vertices.push_back(vertex);

		}

		for (int i = 0; i < triangleCount; i++) {
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}
		VertexArrayObject* vao = new VertexArrayObject();
		vao->build(vertices, indices);
		// kaplamalý yuvarlak
		VAOMap["circleTex"] = vao;
	}

	Mesh* mesh = new Mesh();
	mesh->vao = VAOMap["circleTex"];
	mesh->vertexCount = VAOMap["circleTex"]->getVertexCount();
	mesh->indexCount = VAOMap["circleTex"]->getIndexCount();

	return mesh;
}
