#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include <string>
#include <map>
#include <vector>

class TextureManager {
public:
	static TextureManager* getInstance();
	unsigned int loadTexture(std::string fileName);
	unsigned int loadCubeMapTexture(std::vector<std::string> faces);
	void activateTexture(unsigned int level, unsigned int id);
	void activateCubeMapTexture(unsigned int id);
	void deleteTexture(unsigned int id);
private:
	TextureManager();
	static TextureManager* m_Instance;
	std::map<std::string, unsigned int> m_TextureMap;
};
#endif // !TEXTUREMANAGER_HPP