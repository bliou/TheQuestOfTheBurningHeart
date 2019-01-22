#pragma once
#include "DrawableComponent.h"
#include <anax/System.hpp>
#include <Box2D/Box2D.h>

enum class RenderElement {
	FIX_LAYER = 0x0001,
	TILE_LAYER = 0x0002,
	REST = 0x0004
};

class DrawableRenderingSystem: public anax::System<anax::Requires<
	DrawableComponent
	>>
{
public:
	DrawableRenderingSystem();

	virtual void render(
		sf::RenderWindow& window,
		uint16 renderElements = 0x0007);
};

