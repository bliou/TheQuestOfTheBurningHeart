#pragma once
#include <anax/System.hpp>
#include "EndFootCollisionComponent.h"
#include "CharacterComponent.h"

class EndFootCollisionSystem: public anax::System<anax::Requires<
	EndFootCollisionComponent,
	CharacterComponent>>
{
public:
	EndFootCollisionSystem();

	void update(float elapsedTime);
};

