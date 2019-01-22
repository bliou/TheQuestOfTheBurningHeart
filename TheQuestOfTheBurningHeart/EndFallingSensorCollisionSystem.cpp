#include "EndFallingSensorCollisionSystem.h"
#include "GroundCharacterStateComponent.h"


EndFallingSensorCollisionSystem::EndFallingSensorCollisionSystem()
{
}

void EndFallingSensorCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& fallingComponent = entity.getComponent<FallingTriggerComponent>();
		auto& sensorsCount = fallingComponent.sensorsCount;
		--sensorsCount;
		if (sensorsCount <= 0) {
			sensorsCount = 0;

			auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
			if (state != GroundCharacterState::DYING)
			{
				auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
				if (orientation == CharacterOrientation::LEFT)
					orientation = CharacterOrientation::RIGHT;
				else
					orientation = CharacterOrientation::LEFT;
			}
		}
		entity.removeComponent<EndFallingSensorCollisionComponent>();
		entity.activate();
	}
}