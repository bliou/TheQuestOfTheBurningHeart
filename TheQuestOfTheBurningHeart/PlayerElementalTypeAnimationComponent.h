#pragma once
#include "ElementalType.h"
#include <anax/Component.hpp>
#include <map>

struct PlayerElementalTypeAnimationComponent : anax::Component {
	std::map<ElementalType, float> typeOffset;
};