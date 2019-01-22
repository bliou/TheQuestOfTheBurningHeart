#pragma once
#include "ResetTileComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>

class ResetTileRenderingSystem : public anax::System<anax::Requires<
	ResetTileComponent,
	DrawableComponent
	>>
{
public:
	ResetTileRenderingSystem();
	
	void render(sf::RenderWindow& window);
};

