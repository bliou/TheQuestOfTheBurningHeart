#pragma once
#include "StartEntityCollisionComponent.h"
#include <anax/System.hpp>

class GameScreen;

class StartEntityCollisionSystem: public anax::System<anax::Requires<StartEntityCollisionComponent>>
{
public:
	StartEntityCollisionSystem(GameScreen& gameInstance);
	
	void update(float elapsedTime);

protected:
	GameScreen & m_gameInstance;

	void playerLoseLife(anax::Entity& player);
};

