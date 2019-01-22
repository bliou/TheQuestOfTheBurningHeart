#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <list>

enum class Font {
	ARIAL = 0,
	CURLZ = 1
};

class FontsManager
{
public:
	FontsManager();
	~FontsManager();

	static void loadEntities(Font font);
	static sf::Font& getFont(Font font);

private:
	static std::string fontFolder;
	static std::map<std::string, sf::Font*> fonts;
	static std::map<Font, std::string> allowedFonts;
};