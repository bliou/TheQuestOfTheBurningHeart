#include "TimedTileSystem.h"
#include "ResetTileComponent.h"
#include "DisableComponent.h"

TimedTileSystem::TimedTileSystem()
{
}

void TimedTileSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& timedTileComponent = entity.getComponent<TimedTileComponent>();
		if (timedTileComponent.active) {
			timedTileComponent.currentTimer -= elapsedTime;
			if (timedTileComponent.currentTimer <= 0.f) {
				timedTileComponent.active = false;
				timedTileComponent.currentTimer = timedTileComponent.defaultTimer;
				if (entity.hasComponent<ResetTileComponent>()) {
					entity.getComponent<ResetTileComponent>().activated = true;
					entity.addComponent<DisableComponent>();
					entity.activate();
				}
				else {
					entity.kill();
					entity.activate();
				}
			}
		}
	}
}