#pragma once
#include "MonsterComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>

class MonsterRenderingSystem: public anax::System<anax::Requires<
	MonsterComponent,
	DrawableComponent
	>>
{
public:
	MonsterRenderingSystem();

	void render(sf::RenderWindow& window);
};

