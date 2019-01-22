#include "StartFootCollisionSystem.h"
#include "TileComponent.h"
#include "GamePlayerComponent.h"
#include "DisableComponent.h"
#include "TimedTileComponent.h"
#include "MonsterComponent.h"
#include "GroundCharacterStateComponent.h"
#include "LifeComponent.h"
#include "DyingComponent.h"
#include "DamagedComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include "VelocityComponent.h"
#include "SoundsManager.h"
#include "PlayerJumpLoaderComponent.h"
#include "SlopeTileComponent.h"
#include "CharacterSlopeTileComponent.h"
#include "CharacterOrientationComponent.h"
#include "ChickenBossPatternComponent.h"
#include "CloseAttackPatternComponent.h"
#include "RangeAttackPatternComponent.h"

StartFootCollisionSystem::StartFootCollisionSystem()
{

}

void StartFootCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities) 
	{
		auto collidedEntitiesId = entity.getComponent<StartFootCollisionComponent>().collidedEntitiesId;
		auto& characterComponent = entity.getComponent<CharacterComponent>();
		for (uint64_t collidedEntityId : collidedEntitiesId)
		{
			anax::Entity collidedEntity = entity.getWorld().getEntity(collidedEntityId);

			if (collidedEntity.hasComponent<TileComponent>()) {
				if (collidedEntity.getComponent<TileComponent>().collideFoot)
					characterComponent.footContacts.push_back(collidedEntityId);
				if (collidedEntity.hasComponent<SlopeTileComponent>()) {
					if (entity.hasComponent<CharacterSlopeTileComponent>())
						entity.removeComponent<CharacterSlopeTileComponent>();
					auto& slopeType = collidedEntity.getComponent<SlopeTileComponent>().slopeType;
					entity.addComponent<CharacterSlopeTileComponent>(collidedEntityId, slopeType);
				}
			}

			if (entity.hasComponent<GamePlayerComponent>()
				&& !collidedEntity.hasComponent<DisableComponent>()) {
				if (collidedEntity.hasComponent<TimedTileComponent>())
					collidedEntity.getComponent<TimedTileComponent>().active = true;

				if (collidedEntity.hasComponent<MonsterComponent>()
					&& collidedEntity.hasComponent<GroundCharacterStateComponent>()) {
					auto& monsterState = collidedEntity.getComponent<GroundCharacterStateComponent>().state;
					auto& playerState = entity.getComponent<GroundCharacterStateComponent>().state;
					if (monsterState != GroundCharacterState::DYING
						&& monsterState != GroundCharacterState::DAMAGED
						&& (playerState == GroundCharacterState::FALL)) {
						monsterLoseLife(collidedEntity);
						SoundsManager::playSound(SoundType::HIT);
						entity.getComponent<GroundCharacterStateComponent>().state = GroundCharacterState::JUMP;
						entity.addComponent<PlayerJumpLoaderComponent>(0.02f);
						auto& velocity = entity.getComponent<CharacterComponent>().velocity;
						entity.getComponent<VelocityComponent>().velocity.y = velocity.y;

						characterComponent.footContacts.clear();
					}
				}
			}
		}
		entity.removeComponent<StartFootCollisionComponent>();
		entity.activate();
	}
}

void StartFootCollisionSystem::monsterLoseLife(anax::Entity& monster)
{
	auto& state = monster.getComponent<GroundCharacterStateComponent>().state;
	auto& lifes = monster.getComponent<LifeComponent>().lifes;
	lifes--;
	if (lifes <= 0) {
		state = GroundCharacterState::DYING;
		monster.addComponent<DyingComponent>();
	}
	else {
		state = GroundCharacterState::DAMAGED;
		monster.addComponent<DamagedComponent>();
		if (monster.hasComponent<ChickenBossPatternComponent>()) {
			auto& patternComponent = monster.getComponent<ChickenBossPatternComponent>();
			patternComponent.currentRangeAttackCounter = patternComponent.rangeAttackCounter;
		}
		if (monster.hasComponent<CloseAttackPatternComponent>()) {
			monster.removeComponent<CloseAttackPatternComponent>();
			monster.activate();
		}
		if (monster.hasComponent<RangeAttackPatternComponent>()) {
			monster.removeComponent<RangeAttackPatternComponent>();
			monster.activate();
		}
	}
}