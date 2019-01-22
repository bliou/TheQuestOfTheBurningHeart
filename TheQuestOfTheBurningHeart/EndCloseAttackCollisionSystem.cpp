#include "EndCloseAttackCollisionSystem.h"
#include "CloseAttackPatternComponent.h"
#include "GroundCharacterStateComponent.h"


EndCloseAttackCollisionSystem::EndCloseAttackCollisionSystem()
{
}

void EndCloseAttackCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<CloseAttackPatternComponent>())
			entity.getComponent<CloseAttackPatternComponent>().removed = true;

		entity.removeComponent<EndCloseAttackCollisionComponent>();
		entity.activate();
	}
}