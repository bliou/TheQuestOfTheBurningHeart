#pragma once
#include "DoorTileComponent.h"
#include <anax/System.hpp>

class GameScreen;

class DoorTileInputSystem : public anax::System<anax::Requires<
	DoorTileComponent
	>>
{
public:
	DoorTileInputSystem(GameScreen& gameInstance);

	void updateEvent();

protected:
	GameScreen & m_gameInstance;
};

