#pragma once
#include "SpriteBox.h"
#include <vector>

struct AnimationStateComponent {
	AnimationStateComponent() :
		spriteBoxes(),
		animationTimer(0.0f)
	{
	}

	AnimationStateComponent(
		std::vector<SpriteBox> spriteBoxes,
		float animationTimer = 0.f)
	{
		this->spriteBoxes = spriteBoxes;
		this->animationTimer = animationTimer;
	}

	/// The boxes used to draw the sprite
	std::vector<SpriteBox> spriteBoxes;

	/// The current animation timer
	float animationTimer;
};