#include "ActivateTileAnimationSystem.h"
#include "CheckpointTileComponent.h"
#include "BreakableTileComponent.h"

ActivateTileAnimationSystem::ActivateTileAnimationSystem()
{
}

void ActivateTileAnimationSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& animationComponent = entity.getComponent<AnimationComponent>();
		auto& activateAnimationComponent = entity.getComponent<ActivateTileAnimationComponent>();
		if (entity.hasComponent<CheckpointTileComponent>()) {
			bool activated = entity.getComponent<CheckpointTileComponent>().isUsed;
			animationComponent.state = activateAnimationComponent.states[activated];
		}
		if (entity.hasComponent<BreakableTileComponent>()) {
			bool broken = entity.getComponent<BreakableTileComponent>().broken;
			animationComponent.state = activateAnimationComponent.states[broken];
			animationComponent.setAnimationTimer = true;
		}
	}
}