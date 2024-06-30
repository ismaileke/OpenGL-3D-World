#ifndef VERTEXTYPES_HPP
#define VERTEXTYPES_HPP
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

class Vertex3DTexture {
public:
	glm::vec3 position;
	glm::vec2 texture;
};

typedef std::vector<unsigned int>    IndexList;
typedef std::vector<glm::vec3>       PositionList;
typedef std::vector<glm::vec2>	     TextureList;
typedef std::vector<Vertex3DTexture> Vertex3DTextureList;

#endif