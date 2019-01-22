#pragma once
#include <map>

enum class SoundType {
	PLAYER_LIFE = 0,
	PLAYER_DEATH = 1,
	PLAYER_JUMP = 2,
	COIN = 3,
	HIT = 4,
	SURPRISE = 5
};

const std::map<SoundType, std::string> soundsMap = {
	{ SoundType::PLAYER_LIFE, "Resources/Sounds/playerLife.wav" },
	{ SoundType::PLAYER_DEATH, "Resources/Sounds/playerDeath.wav" },
	{ SoundType::PLAYER_JUMP, "Resources/Sounds/playerJump.wav" },
	{ SoundType::COIN, "Resources/Sounds/coin.wav" },
	{ SoundType::HIT, "Resources/Sounds/hit.wav" },
	{ SoundType::SURPRISE, "Resources/Sounds/surprise.wav"}
};