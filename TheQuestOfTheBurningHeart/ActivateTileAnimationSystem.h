#pragma once
#include "AnimationComponent.h"
#include "ActivateTileAnimationComponent.h"
#include <anax/System.hpp>

class ActivateTileAnimationSystem: public anax::System<anax::Requires<
	ActivateTileAnimationComponent,
	AnimationComponent
	>>
{
public:
	ActivateTileAnimationSystem();

	void update(float elapsedTime);
};

