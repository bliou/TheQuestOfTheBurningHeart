#pragma once
#include <anax/Component.hpp>

struct CloseAttackDataComponent : anax::Component {
	CloseAttackDataComponent(float timer)
		: closeAttackTimer(timer)
	{

	}

	const float closeAttackTimer;
};