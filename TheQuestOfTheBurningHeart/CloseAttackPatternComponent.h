#pragma once
#include "CharacterOrientation.h"
#include <anax/Component.hpp>

struct CloseAttackPatternComponent : anax::Component {
	CloseAttackPatternComponent(
		uint64_t pId, 
		float timer,
		CharacterOrientation orientation)
		: playerId(pId),
		removed(false),
		currentTimer(timer),
		previousOrientation(orientation)
	{

	}

	float currentTimer;
	const uint64_t playerId;
	bool removed;
	CharacterOrientation previousOrientation;
};