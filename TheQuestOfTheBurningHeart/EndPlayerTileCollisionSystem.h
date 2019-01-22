#pragma once
#include <anax/System.hpp>
#include "EndEntityCollisionComponent.h"
#include "GamePlayerComponent.h"

class EndPlayerTileCollisionSystem : public anax::System<anax::Requires<
	EndEntityCollisionComponent,
	GamePlayerComponent
>>
{
public:
	EndPlayerTileCollisionSystem();

	void update(float elapsedTime);
};

