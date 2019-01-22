#pragma once
#include "StartMonsterSensorCollisionComponent.h"
#include "CharacterOrientationComponent.h"
#include <anax/System.hpp>

class StartMonsterSensorCollisionSystem: public anax::System<anax::Requires<
	StartMonsterSensorCollisionComponent,
	CharacterOrientationComponent>>
{
public:
	StartMonsterSensorCollisionSystem();

	void update(float elapsedTime);
};

