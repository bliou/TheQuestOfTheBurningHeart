#include "StartMonsterSensorCollisionSystem.h"
#include "PositionComponent.h"

StartMonsterSensorCollisionSystem::StartMonsterSensorCollisionSystem()
{
}

void StartMonsterSensorCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
		if (orientation == CharacterOrientation::LEFT)
			orientation = CharacterOrientation::RIGHT;
		else
			orientation = CharacterOrientation::LEFT;

		entity.removeComponent<StartMonsterSensorCollisionComponent>();
		entity.activate();
	}
}
