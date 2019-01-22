#pragma once
#include "ProjectileComponent.h"
#include <anax/System.hpp>

class ProjectileClearSystem: public anax::System<anax::Requires<
	ProjectileComponent
	>>
{
public:
	ProjectileClearSystem();

	void update(float elapsedTime);
};

