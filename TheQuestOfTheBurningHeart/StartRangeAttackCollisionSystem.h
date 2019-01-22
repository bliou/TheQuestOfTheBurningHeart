#pragma once
#include "StartRangeAttackCollisionComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include "RangeAttackDataComponent.h"
#include <anax/System.hpp>

class StartRangeAttackCollisionSystem: public anax::System<anax::Requires<
	StartRangeAttackCollisionComponent,
	RangeAttackDataComponent,
	CharacterComponent,
	CharacterOrientationComponent>>
{
public:
	StartRangeAttackCollisionSystem();

	void update(float elapsedTime);
};

