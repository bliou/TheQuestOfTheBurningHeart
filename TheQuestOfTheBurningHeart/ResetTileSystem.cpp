#include "ResetTileSystem.h"
#include "DisableComponent.h"


ResetTileSystem::ResetTileSystem()
{
}

void ResetTileSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& resetTileComponent = entity.getComponent<ResetTileComponent>();
		if (resetTileComponent.activated) {
			resetTileComponent.currentTimer -= elapsedTime;
			if (resetTileComponent.currentTimer <= 0.f) {
				resetTileComponent.activated = false;
				resetTileComponent.currentTimer = resetTileComponent.defaultTimer;
				entity.removeComponent<DisableComponent>();
				entity.activate();
			}
		}
	}
}