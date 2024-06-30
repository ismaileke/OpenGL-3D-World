#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP
#include <map>
#include <string>

class Mesh;
class VertexArrayObject;

using namespace std;

class MeshManager {
public:
	static MeshManager* getInstance();
	Mesh* buildCube();
	Mesh* buildSquare(float length);
	Mesh* buildPyramid();
	Mesh* buildCircle(float radius, int vertexCount);
private:
	MeshManager();
	static MeshManager* m_Instance;
	map<string, VertexArrayObject*> VAOMap;
};
#endif