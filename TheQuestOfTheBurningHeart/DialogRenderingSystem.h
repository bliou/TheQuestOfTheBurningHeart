#pragma once
#include "DialogComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>

class DialogRenderingSystem: public anax::System<anax::Requires<
	DialogComponent,
	DrawableComponent
	>>
{
public:
	DialogRenderingSystem();

	void render(sf::RenderWindow& window);
};

