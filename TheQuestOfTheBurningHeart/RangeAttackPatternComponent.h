#pragma once
#include <anax/Component.hpp>

struct RangeAttackPatternComponent : anax::Component {
	RangeAttackPatternComponent(
		int count,
		float as)
		: rangeAttackCount(count),
		attackTimer(as)
	{

	}

	int rangeAttackCount;
	float attackTimer;
};