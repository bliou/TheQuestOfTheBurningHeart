#pragma once
#include "GroundCharacterState.h"
#include "AnimationStateComponent.h"
#include <anax/Component.hpp>
#include <map>

struct GroundCharacterAnimationComponent : anax::Component
{
	GroundCharacterAnimationComponent()
		: currentState(GroundCharacterState::IDLE)
	{

	}

	/// A map to describe the animations the entity has
	std::map<GroundCharacterState, AnimationStateComponent> states;

	GroundCharacterState currentState;
};