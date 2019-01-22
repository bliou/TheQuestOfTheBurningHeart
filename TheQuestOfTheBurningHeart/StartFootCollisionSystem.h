#pragma once
#include <anax/System.hpp>
#include "StartFootCollisionComponent.h"
#include "CharacterComponent.h"

class StartFootCollisionSystem: public anax::System<anax::Requires<
	StartFootCollisionComponent,
	CharacterComponent>>
{
public:
	StartFootCollisionSystem();

	void update(float elapsedTime);

protected:
	void monsterLoseLife(anax::Entity& monster);
};

