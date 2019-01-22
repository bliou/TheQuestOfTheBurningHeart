#pragma once
#include "TransitionType.h"
#include <anax/Component.hpp>

struct TransitionComponent : anax::Component {
	TransitionComponent(
		float per,
		TransitionType type)
		: period(per),
		maxPeriod(per),
		transitionType(type)
	{

	}

	float period;
	const float maxPeriod;
	const TransitionType transitionType;
};