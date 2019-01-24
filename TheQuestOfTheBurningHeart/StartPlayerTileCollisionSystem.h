#pragma once
#include <anax/System.hpp>
#include "StartEntityCollisionComponent.h"
#include "CharacterComponent.h"

class GameScreen;

class StartPlayerTileCollisionSystem : public anax::System<anax::Requires<
	StartEntityCollisionComponent,
	CharacterComponent>>
{
public:
	StartPlayerTileCollisionSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen& m_gameInstance;
};

