#pragma once
#include "KillComponent.h"
#include <anax/System.hpp>

class KillSystem: public anax::System<anax::Requires<
	KillComponent
	>>
{
public:
	KillSystem();

	void update();
};

