#include "StartRangeAttackCollisionSystem.h"
#include "GroundCharacterStateComponent.h"
#include "RangeAttackPatternComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"


StartRangeAttackCollisionSystem::StartRangeAttackCollisionSystem()
{
}

void StartRangeAttackCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
		state = GroundCharacterState::RANGE_ATTACK;

		auto& rangeAttackData = entity.getComponent<RangeAttackDataComponent>();
		entity.addComponent<RangeAttackPatternComponent>(
			rangeAttackData.rangeAttackCount,
			rangeAttackData.attackSpeed
		);

		uint64_t collidedEntityId = entity.getComponent<StartRangeAttackCollisionComponent>().collidedEntityId;
		anax::Entity player = entity.getWorld().getEntity(collidedEntityId);
		auto& playerPos = player.getComponent<PositionComponent>().position;
		auto& monsterPos = entity.getComponent<PositionComponent>().position;
		auto& monsterSize = entity.getComponent<SizeComponent>().size;
		auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
		
		if (playerPos.x >= monsterPos.x + monsterSize.x / 2) {
			orientation = CharacterOrientation::RIGHT;
		}
		else {
			orientation = CharacterOrientation::LEFT;
		}

		entity.removeComponent<StartRangeAttackCollisionComponent>();
		entity.activate();
	}
}