#include "TexturesManager.h"

std::map<std::string, sf::Texture*> TexturesManager::textures;
std::list<std::string> TexturesManager::textureFolders{
#ifdef _DEBUG
	"Resources/Images/Debug/",
#else
	"Resources/Images/Release/",
#endif
	"Resources/Images/Layers/"
};


TexturesManager::TexturesManager()
{
}


TexturesManager::~TexturesManager()
{
	std::map<std::string, sf::Texture*>::iterator it = textures.begin();
	for (it; it != textures.end(); ++it) {
		delete (*it).second;
		(*it).second = nullptr;
	}
}

void TexturesManager::loadEntities(std::list<std::string> textureNames)
{
	for (std::string textureName : textureNames)
		loadEntities(textureName);
}

void TexturesManager::loadEntities(std::string textureName)
{
	if (textures.count(textureName) == 0) {
		// If the sound does not exist, we have to load it
		// from the file
		sf::Texture* texture = new sf::Texture();
		for (std::string textureFolder : textureFolders) {
			if (texture->loadFromFile(textureFolder + textureName))
				break;
		}

		textures[textureName] = texture;
	}
}

sf::Texture& TexturesManager::getTexture(std::string textureName)
{
	loadEntities(textureName);
	return *textures[textureName];
}