#pragma once
#include "GamePlayerComponent.h"
#include "PlayerElementalTypeComponent.h"
#include <anax/System.hpp>

class PlayerElementalTypeSystem: public anax::System<anax::Requires<
	GamePlayerComponent,
	PlayerElementalTypeComponent
	>>
{
public:
	PlayerElementalTypeSystem();

	void update(float elapsedTime);
};

