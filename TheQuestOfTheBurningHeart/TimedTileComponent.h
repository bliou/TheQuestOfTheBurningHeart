#pragma once
#include <anax/Component.hpp>

struct TimedTileComponent : anax::Component {
	TimedTileComponent(float timer)
		: defaultTimer(timer),
		currentTimer(timer),
		active(false)
	{

	}

	const float defaultTimer;
	float currentTimer;
	bool active;
};