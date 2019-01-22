#pragma once
#include "CharacterComponent.h"
#include "PhysicComponent.h"
#include "PositionComponent.h"
#include <anax/System.hpp>

class CharacterMovingTileSystem: public anax::System<anax::Requires<
	CharacterComponent,
	PhysicComponent
	>>
{
public:
	CharacterMovingTileSystem();

	void update(float elapsedTime);
};

