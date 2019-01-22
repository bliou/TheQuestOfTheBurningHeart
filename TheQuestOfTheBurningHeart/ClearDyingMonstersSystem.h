#pragma once
#include "MonsterComponent.h"
#include "DyingComponent.h"
#include <anax/System.hpp>

class ClearDyingMonstersSystem: public anax::System<anax::Requires<
	MonsterComponent,
	DyingComponent>>
{
public:
	ClearDyingMonstersSystem();

	void update(float elapsedTime);
};

