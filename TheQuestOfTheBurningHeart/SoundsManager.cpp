#include "SoundsManager.h"
#include <stdexcept>

std::map<SoundType, SoundWrapper*> SoundsManager::sounds;


SoundsManager::SoundsManager()
{
}


SoundsManager::~SoundsManager()
{
	std::map<SoundType, SoundWrapper*>::iterator it = sounds.begin();
	for (it; it != sounds.end(); ++it) {
		delete (*it).second;
		(*it).second = nullptr;
	}
}

void SoundsManager::loadSound(SoundType soundType)
{
	if (sounds.count(soundType) != 0)
		return;
	std::string soundName = soundsMap.at(soundType);
	SoundWrapper* soundWrapper = new SoundWrapper();
	soundWrapper->soundBuffer.loadFromFile(soundName);
	soundWrapper->sound.setBuffer(soundWrapper->soundBuffer);
	sounds[soundType] = soundWrapper;
}

void SoundsManager::playSound(SoundType soundType)
{
	loadSound(soundType);

	sounds[soundType]->sound.play();
}
