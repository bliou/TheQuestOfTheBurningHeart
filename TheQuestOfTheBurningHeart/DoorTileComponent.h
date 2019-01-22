#pragma once
#include "Screen.h"
#include <anax/Component.hpp>

struct DoorTileComponent : anax::Component {

	DoorTileComponent(Screen next)
		: activated(false),
		nextScreen(next)
	{
		clearConfig = nextScreen != Screen::GAME;
	}
	
	bool activated;
	bool clearConfig;
	Screen nextScreen;
};