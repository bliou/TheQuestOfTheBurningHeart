#pragma once
#include "GameScreen.h"

class AnimationActionFactory
{
public:
	AnimationActionFactory();
	~AnimationActionFactory();

	void createAnimationActions(
		nlohmann::json& animationJson,
		GameScreen& gameInstance,
		const float currentTimer);

protected:
	void createAnimationAction(
		nlohmann::json::value_type data,
		GameScreen& gameInstance,
		bool& isBlocked);
};

