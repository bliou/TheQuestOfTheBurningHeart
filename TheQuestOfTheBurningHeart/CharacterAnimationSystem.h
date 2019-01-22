#pragma once
#include "AnimationComponent.h"
#include "DrawableComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include <anax/System.hpp>

class CharacterAnimationSystem: public anax::System<anax::Requires<
	DrawableComponent,
	AnimationComponent,
	CharacterComponent,
	CharacterOrientationComponent
	>>
{
public:
	CharacterAnimationSystem();

	void update(float elapsedTime);
};

