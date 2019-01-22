#include "FontsManager.h"


std::map<std::string, sf::Font*> FontsManager::fonts;
std::string FontsManager::fontFolder = "Resources/Fonts/";
std::map<Font, std::string> FontsManager::allowedFonts{
	{ Font::ARIAL, "arial.ttf" },
	{ Font::CURLZ, "curlz.ttf" }
};

FontsManager::FontsManager()
{
}


FontsManager::~FontsManager()
{
	std::map<std::string, sf::Font*>::iterator it = fonts.begin();
	for (it; it != fonts.end(); ++it) {
		delete (*it).second;
		(*it).second = nullptr;
	}
}

void FontsManager::loadEntities(Font fontEnum)
{
	std::string fontName = allowedFonts[fontEnum];
	if (fonts.count(fontName) == 0) {
		// If the sound does not exist, we have to load it
		// from the file
		sf::Font* font = new sf::Font();
		font->loadFromFile(fontFolder + fontName);
		fonts[fontName] = font;
	}
}

sf::Font& FontsManager::getFont(Font fontEnum)
{
	loadEntities(fontEnum);
	std::string fontName = allowedFonts[fontEnum];
	return *fonts[fontName];
}