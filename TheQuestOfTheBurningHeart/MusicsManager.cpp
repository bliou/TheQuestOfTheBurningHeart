#include "MusicsManager.h"

std::map<std::string, sf::Music*> MusicsManager::musics;


MusicsManager::MusicsManager()
{
}


MusicsManager::~MusicsManager()
{
	auto it = musics.begin();
	for (it; it != musics.end(); ++it) {
		delete (*it).second;
		(*it).second = nullptr;
	}
}

void MusicsManager::loadMusic(std::string musicName)
{
	sf::Music* music = new sf::Music();
	music->openFromFile("Resources/Musics/" + musicName);
	music->setLoop(true);
	music->setVolume(10.f);

	musics[musicName] = music;
}

void MusicsManager::playMusic(std::string musicName)
{
	if (musics.count(musicName) == 0)
		loadMusic(musicName);

	musics.at(musicName)->play();
}

void MusicsManager::stopMusic()
{
	for (auto& music : musics)
	{
		music.second->stop();
	}
}