#pragma once
#include "SoundType.h"
#include <SFML/Audio.hpp>
#include <list>
#include <map>


struct SoundWrapper {
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
};

class SoundsManager
{
public:
	SoundsManager();
	~SoundsManager();

	static void loadSound(SoundType soundType);
	static void playSound(SoundType soundType);

private:
	static std::map<SoundType, SoundWrapper*> sounds;

};