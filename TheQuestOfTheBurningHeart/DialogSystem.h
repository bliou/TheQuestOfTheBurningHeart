#pragma once
#include "DialogComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>

class DialogSystem: public anax::System<anax::Requires<
	DialogComponent,
	DrawableComponent
	>>
{
public:
	DialogSystem();

	void update(float elapsedTime);

protected:
	static const float updateContent;
};

