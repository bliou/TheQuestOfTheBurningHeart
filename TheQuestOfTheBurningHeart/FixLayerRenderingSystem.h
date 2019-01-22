#pragma once
#include "DrawableComponent.h"
#include "FixLayerComponent.h"
#include <SFML/Graphics.hpp>
#include <anax/System.hpp>

class FixLayerRenderingSystem: public anax::System<anax::Requires<
	DrawableComponent,
	FixLayerComponent
	>>
{
public:
	FixLayerRenderingSystem();

	void render(sf::RenderWindow& window);
};

