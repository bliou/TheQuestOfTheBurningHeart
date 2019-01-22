#pragma once
#include "AnimationComponent.h"
#include "DrawableComponent.h"
#include <anax/System.hpp>

class AnimationSystem : public anax::System<anax::Requires<
	DrawableComponent, 
	AnimationComponent
	>>
{
public:
	AnimationSystem();

	void update(float elapsedTime);

private:
	float m_timer;
};

