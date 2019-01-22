#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <list>

class TexturesManager
{
public:
	TexturesManager();
	~TexturesManager();

	static void loadEntities(std::string textureName);
	static void loadEntities(std::list<std::string> textureNames);

	static sf::Texture& getTexture(std::string textureName);

private:
	static std::list<std::string> textureFolders;
	static std::map<std::string, sf::Texture*> textures;
};

