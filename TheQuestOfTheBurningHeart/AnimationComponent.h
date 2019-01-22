#pragma once
#include "AnimationStateComponent.h"
#include <anax/Component.hpp>

struct AnimationComponent : anax::Component {
	AnimationComponent() :
		currentFrame(0),
		defaultAnimationTimer(0.f),
		currentAnimationTimer(0.f),
		setAnimationTimer(true)
	{
	};

	/// Resets the animation
	void reset()
	{
		currentFrame = 0;
		setAnimationTimer = true;
		defaultAnimationTimer = 0.f;
		currentAnimationTimer = 0.f;
	}

	/// The current frame number
	int currentFrame;

	/// Is set to true when we want to set the
	/// animation timer
	bool setAnimationTimer;
	
	/// The default animation timer
	float defaultAnimationTimer;

	/// The current animation timer
	float currentAnimationTimer;

	AnimationStateComponent state;
};