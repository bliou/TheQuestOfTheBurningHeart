#include "EndMonsterSensorCollisionSystem.h"

EndMonsterSensorCollisionSystem::EndMonsterSensorCollisionSystem()
{
}

void EndMonsterSensorCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		entity.removeComponent<EndMonsterSensorCollisionComponent>();
		entity.activate();
	}
}