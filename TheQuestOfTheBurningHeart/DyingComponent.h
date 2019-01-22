#pragma once
#include <anax/Component.hpp>

struct DyingComponent: anax::Component
{
	const float maxDyingTimer = 1.f;
	float currentDyingTimer = 1.f;
};

