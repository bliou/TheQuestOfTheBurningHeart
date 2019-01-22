#pragma once
#include "GroundCharacterAnimationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "AnimationComponent.h"
#include <anax/System.hpp>

class GroundCharacterAnimationSystem: public anax::System<anax::Requires<
	GroundCharacterStateComponent,
	GroundCharacterAnimationComponent,
	AnimationComponent>>
{
public:
	GroundCharacterAnimationSystem();

	void update(float elapsedTime);
};

