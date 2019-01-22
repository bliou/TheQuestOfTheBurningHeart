#pragma once
#include "EndEntityCollisionComponent.h"
#include <anax/System.hpp>

class EndEntityCollisionSystem: public anax::System<anax::Requires<EndEntityCollisionComponent>>
{
public:
	EndEntityCollisionSystem();
	
	void update(float elapsedTime);
};

