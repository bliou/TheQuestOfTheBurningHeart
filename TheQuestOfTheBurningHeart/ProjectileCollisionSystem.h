#pragma once
#include "ProjectileCollisionComponent.h"
#include <anax/System.hpp>

class GameScreen;

class ProjectileCollisionSystem: public anax::System<anax::Requires<
	ProjectileCollisionComponent
	>>
{
public:
	ProjectileCollisionSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen& m_gameInstance;
};

