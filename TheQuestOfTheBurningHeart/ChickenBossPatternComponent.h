#pragma once
#include <anax/Component.hpp>

struct ChickenBossPatternComponent : anax::Component {
	ChickenBossPatternComponent()
		: currentRangeAttackCounter(0),
		rangeAttackCounter(3)
	{

	}

	int currentRangeAttackCounter;
	const int rangeAttackCounter;
};