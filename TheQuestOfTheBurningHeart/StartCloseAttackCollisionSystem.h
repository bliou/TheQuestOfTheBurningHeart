#pragma once
#include "StartCloseAttackCollisionComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include "CloseAttackDataComponent.h"
#include <anax/System.hpp>

class StartCloseAttackCollisionSystem: public anax::System<anax::Requires<
	StartCloseAttackCollisionComponent,
	CloseAttackDataComponent,
	CharacterComponent,
	CharacterOrientationComponent>>
{
public:
	StartCloseAttackCollisionSystem();

	void update(float elapsedTime);
};

