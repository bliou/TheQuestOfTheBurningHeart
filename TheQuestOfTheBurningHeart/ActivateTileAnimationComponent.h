#pragma once
#include "AnimationStateComponent.h"
#include <anax/Component.hpp>
#include <map>

struct ActivateTileAnimationComponent : anax::Component {
	std::map<bool, AnimationStateComponent> states;
};