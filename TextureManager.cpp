#include "TextureManager.hpp"
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

TextureManager* TextureManager::m_Instance = 0;

TextureManager::TextureManager() {

}

TextureManager* TextureManager::getInstance()
{
    if (m_Instance) {
        return m_Instance;
    }
    m_Instance = new TextureManager();
    return m_Instance;
}

unsigned int TextureManager::loadTexture(std::string fileName)
{
    unsigned int id = -1;
    if (m_TextureMap.count(fileName) != 0) {
        id = m_TextureMap[fileName];
    }
    else {
        int width, height, nrChannel;
        unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannel, 0);

        GLuint format = GL_RGB;
        if (nrChannel == 4) {
            format = GL_RGBA;
        }

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        m_TextureMap[fileName] = id;
    }
    return id;
}

unsigned int TextureManager::loadCubeMapTexture(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    return textureID;
}

void TextureManager::activateTexture(unsigned int level, unsigned int id)
{
    glActiveTexture(level);
    glBindTexture(GL_TEXTURE_2D, id);
}

void TextureManager::activateCubeMapTexture(unsigned int id) {
    glActiveTexture(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void TextureManager::deleteTexture(unsigned int id) {
    glDeleteTextures(1, &id);
}
