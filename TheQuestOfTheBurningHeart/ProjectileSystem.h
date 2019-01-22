#pragma once
#include "ProjectileComponent.h"
#include <anax/System.hpp>

class ProjectileSystem: public anax::System<anax::Requires<
	ProjectileComponent
	>>
{
public:
	ProjectileSystem();

	void update(float elpasedTime);
};

