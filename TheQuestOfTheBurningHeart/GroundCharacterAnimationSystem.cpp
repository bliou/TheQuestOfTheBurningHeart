#include "GroundCharacterAnimationSystem.h"



GroundCharacterAnimationSystem::GroundCharacterAnimationSystem()
{
}

void GroundCharacterAnimationSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& animationComponent = entity.getComponent<AnimationComponent>();
		auto& groundAnimationComponent = entity.getComponent<GroundCharacterAnimationComponent>();
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;

		if (groundAnimationComponent.currentState != state) {
			groundAnimationComponent.currentState = state;
			animationComponent.state = groundAnimationComponent.states[state];
			animationComponent.reset();
		}
	}
}