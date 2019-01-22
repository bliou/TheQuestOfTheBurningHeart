#pragma once
#include "PlayerElementalTypeAnimationComponent.h"
#include "PlayerElementalTypeComponent.h"
#include "ElementalAnimationOffsetComponent.h"
#include <anax/System.hpp>

class PlayerElementalTypeAnimationSystem: public anax::System<anax::Requires<
	PlayerElementalTypeAnimationComponent,
	PlayerElementalTypeComponent,
	ElementalAnimationOffsetComponent
	>>
{
public:
	PlayerElementalTypeAnimationSystem();

	void update(float elapsedTime);
};

