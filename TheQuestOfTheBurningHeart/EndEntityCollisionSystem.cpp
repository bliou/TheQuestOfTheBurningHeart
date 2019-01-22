#include "EndEntityCollisionSystem.h"



EndEntityCollisionSystem::EndEntityCollisionSystem()
{
}

void EndEntityCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		entity.removeComponent<EndEntityCollisionComponent>();
		entity.activate();
	}
}