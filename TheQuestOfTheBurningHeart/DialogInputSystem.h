#pragma once
#include "DialogComponent.h"
#include <anax/System.hpp>

class DialogInputSystem : public anax::System<anax::Requires<
	DialogComponent
	>>
{
public:
	DialogInputSystem();

	void updateEvent();
};

