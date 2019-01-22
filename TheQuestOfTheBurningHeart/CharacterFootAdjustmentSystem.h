#pragma once
#include "CharacterComponent.h"
#include "PhysicComponent.h"
#include <anax/System.hpp>

class CharacterFootAdjustmentSystem: public anax::System<anax::Requires<
	CharacterComponent,
	PhysicComponent
	>>
{
public:
	CharacterFootAdjustmentSystem();

	void update(float elpasedTime);

protected:
	bool isOneSidedTile(
		anax::Entity* tile,
		anax::Entity* entity);
};

