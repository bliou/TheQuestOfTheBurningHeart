#include "RangeAttackSystem.h"
#include "GroundCharacterStateComponent.h"
#include "GameScreen.h"


RangeAttackSystem::RangeAttackSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void RangeAttackSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& rangePattern = entity.getComponent<RangeAttackPatternComponent>();
		auto& rangeData = entity.getComponent<RangeAttackDataComponent>();
		rangePattern.attackTimer -= elapsedTime;
		if (rangePattern.attackTimer <= 0.f) {
			// CREATE THE PROJECTILE
			auto& position = entity.getComponent<PositionComponent>().position;
			m_gameInstance.addEntityToCreate(
				rangeData.projectileId,
				position + rangeData.offset
			);

			rangePattern.rangeAttackCount--;
			if (rangePattern.rangeAttackCount <= 0) {
				// END OF ATTACK
				if (entity.hasComponent<GroundCharacterStateComponent>()) {
					auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
					state = GroundCharacterState::WALK;
				}

				entity.removeComponent<RangeAttackPatternComponent>();
				entity.activate();
			}
			else {
				rangePattern.attackTimer = rangeData.attackSpeed;
			}
		}
	}
}