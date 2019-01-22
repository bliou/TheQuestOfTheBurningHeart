#include "StartCloseAttackCollisionSystem.h"
#include "GroundCharacterStateComponent.h"
#include "VelocityComponent.h"
#include "CloseAttackTriggerComponent.h"
#include "CloseAttackPatternComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"

StartCloseAttackCollisionSystem::StartCloseAttackCollisionSystem()
{
}

void StartCloseAttackCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		uint64_t collidedEntityId = entity.getComponent<StartCloseAttackCollisionComponent>().collidedEntityId;
		
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
		if (state != GroundCharacterState::DAMAGED
			&& state != GroundCharacterState::RANGE_ATTACK
			&& state != GroundCharacterState::DYING) {
			auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
			float timer = entity.getComponent<CloseAttackDataComponent>().closeAttackTimer;
			entity.addComponent<CloseAttackPatternComponent>(
				collidedEntityId,
				timer,
				orientation
			);

			state = GroundCharacterState::CLOSE_ATTACK;

			anax::Entity player = entity.getWorld().getEntity(collidedEntityId);
			auto& playerPos = player.getComponent<PositionComponent>().position;
			auto& monsterPos = entity.getComponent<PositionComponent>().position;
			auto& monsterSize = entity.getComponent<SizeComponent>().size;

			if (playerPos.x >= monsterPos.x + monsterSize.x / 2) {
				orientation = CharacterOrientation::RIGHT;
			}
			else {
				orientation = CharacterOrientation::LEFT;
			}
		}

		entity.removeComponent<StartCloseAttackCollisionComponent>();
		entity.activate();
	}
}