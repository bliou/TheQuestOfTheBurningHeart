#pragma once
#include "GroundCharacterState.h"
#include <anax/Component.hpp>

struct DamagedComponent : anax::Component {
	const float maxTimer = 1.f;
	float currentTimer = 1.f;
};