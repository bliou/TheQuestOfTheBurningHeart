#pragma once
#include "ScreenCollisionComponent.h"
#include <anax/System.hpp>

class GameScreen;

class ScreenCollisionSystem: public anax::System<anax::Requires<
	ScreenCollisionComponent
	>>
{
public:
	ScreenCollisionSystem(GameScreen& gameInstance);
	
	void update(float elapsedTime);

protected:
	void monsterScreenCollision(
		anax::Entity& monster,
		ScreenSide screenSide);

	void playerScreenCollision(
		anax::Entity& player,
		ScreenSide screenSide);

	GameScreen& m_gameInstance;
};

