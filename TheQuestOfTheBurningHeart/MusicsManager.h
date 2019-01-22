#pragma once
#include <SFML/Audio.hpp>
#include <map>

class MusicsManager
{
public:
	MusicsManager();
	~MusicsManager();

	static void loadMusic(std::string musicName);

	static void playMusic(std::string musicName);
	static void stopMusic();

private:
	static std::map<std::string, sf::Music*> musics;
};

