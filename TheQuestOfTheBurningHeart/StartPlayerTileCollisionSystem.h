#pragma once
#include <anax/System.hpp>
#include "StartEntityCollisionComponent.h"
#include "CharacterComponent.h"

class StartPlayerTileCollisionSystem : public anax::System<anax::Requires<
	StartEntityCollisionComponent,
	CharacterComponent>>
{
public:
	StartPlayerTileCollisionSystem();

	void update(float elapsedTime);
};

