#pragma once
#include "AnimationIdComponent.h"
#include <anax/System.hpp>

class GetAnimationEntityIdSystem: public anax::System<anax::Requires<
	AnimationIdComponent
	>>
{
public:
	GetAnimationEntityIdSystem();

	uint64_t getEntityId(std::string animationId);
};

