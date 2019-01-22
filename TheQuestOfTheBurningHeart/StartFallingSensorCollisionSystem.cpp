#include "StartFallingSensorCollisionSystem.h"



StartFallingSensorCollisionSystem::StartFallingSensorCollisionSystem()
{
}

void StartFallingSensorCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& fallingComponent = entity.getComponent<FallingTriggerComponent>();
		++ fallingComponent.sensorsCount;
		entity.removeComponent<StartFallingSensorCollisionComponent>();
		entity.activate();
	}
}
