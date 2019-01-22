#pragma once
#include "TimedTileComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>
#include <SFML/Graphics.hpp>

class TimedTileRenderingSystem: public anax::System<anax::Requires<
	TimedTileComponent,
	DrawableComponent
	>>
{
public:
	TimedTileRenderingSystem();

	void render(sf::RenderWindow& window);
};

