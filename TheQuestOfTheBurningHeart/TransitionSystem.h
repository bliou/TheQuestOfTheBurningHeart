#pragma once
#include "TransitionComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>

class TransitionSystem: public anax::System<anax::Requires<
	TransitionComponent,
	DrawableComponent
	>>
{
public:
	TransitionSystem();

	void update(float elapsedTime);

protected:
	void updateColor(
		TransitionComponent& transitionComponent,
		sf::Color& color
	);
};

