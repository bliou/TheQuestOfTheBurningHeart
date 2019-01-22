#pragma once
#include "EndMonsterSensorCollisionComponent.h"
#include <anax/System.hpp>

class EndMonsterSensorCollisionSystem : public anax::System<anax::Requires<
	EndMonsterSensorCollisionComponent>>
{
public:
	EndMonsterSensorCollisionSystem();

	void update(float elapsedTime);
};

