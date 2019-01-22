#pragma once
#include <anax/Component.hpp>

struct ResetTileComponent : anax::Component {
	ResetTileComponent(float timer)
		: defaultTimer(timer),
		currentTimer(timer),
		activated(false)
	{

	}
	
	const float defaultTimer;
	float currentTimer;
	bool activated;
};