#pragma once
#include "DrawableComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include <anax/System.hpp>

class SpriteRenderingSystem: public anax::System<anax::Requires<
	DrawableComponent,
	PositionComponent,
	SizeComponent>>
{
public:
	SpriteRenderingSystem();

	void render(sf::RenderTarget& renderTarget);
};

