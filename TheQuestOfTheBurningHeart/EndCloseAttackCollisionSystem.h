#pragma once
#include "EndCloseAttackCollisionComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include <anax/System.hpp>

class EndCloseAttackCollisionSystem : public anax::System<anax::Requires<
	EndCloseAttackCollisionComponent,
	CharacterComponent,
	CharacterOrientationComponent>>
{
public:
	EndCloseAttackCollisionSystem();

	void update(float elapsedTime);
};

