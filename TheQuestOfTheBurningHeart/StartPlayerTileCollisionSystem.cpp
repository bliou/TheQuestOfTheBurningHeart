#include "StartPlayerTileCollisionSystem.h"
#include "CheckpointTileComponent.h"
#include "DoorTileComponent.h"
#include "HelperTileComponent.h"
#include "BonusTileComponent.h"
#include "ElementalTileComponent.h"
#include "PositionComponent.h"
#include "LifeComponent.h"
#include "PlayerCoinsComponent.h"
#include "PlayerElementalTypeComponent.h"
#include "ElementalTypeComponent.h"
#include "ElementalType.h"
#include "ResetTileComponent.h"
#include "DisableComponent.h"
#include "SoundsManager.h"

StartPlayerTileCollisionSystem::StartPlayerTileCollisionSystem()
{
}

void StartPlayerTileCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities) {
		auto collidedEntitiesId = entity.getComponent<StartEntityCollisionComponent>().collidedEntitiesId;
		for (uint64_t collidedEntityId : collidedEntitiesId)
		{
			anax::Entity collidedEntity = entity.getWorld().getEntity(collidedEntityId);

			if (collidedEntity.hasComponent<CheckpointTileComponent>()
				&& !collidedEntity.getComponent<CheckpointTileComponent>().isUsed) {
				auto& ctComponent = collidedEntity.getComponent<CheckpointTileComponent>();
				ctComponent.isUsed = true;

				sf::Vector2f position = entity.getComponent<PositionComponent>().position;
				entity.removeComponent<PositionComponent>();
				entity.addComponent<PositionComponent>(sf::Vector2f(
					position.x,
					position.y - 1
				));
				entity.activate();
			}
			if (collidedEntity.hasComponent<DoorTileComponent>())
			{
				auto& doorComponent = collidedEntity.getComponent<DoorTileComponent>();
				doorComponent.activated = true;
			}
			if (collidedEntity.hasComponent<HelperTileComponent>())
			{
				auto& helperComponent = collidedEntity.getComponent<HelperTileComponent>();
				helperComponent.activated = true;
			}
			if (collidedEntity.hasComponent<BonusTileComponent>())
			{
				BonusType bonusType = collidedEntity.getComponent<BonusTileComponent>().bonusType;

				auto& playerLifes = entity.getComponent<LifeComponent>().lifes;
				auto& playerCoins = entity.getComponent<PlayerCoinsComponent>().coins;

				switch (bonusType)
				{
				case BonusType::HEART:
					playerLifes += 1;
					SoundsManager::playSound(SoundType::PLAYER_LIFE);
					break;
				case BonusType::COPPER_COIN:
					playerCoins += 1;
					SoundsManager::playSound(SoundType::COIN);
					break;
				case BonusType::SILVER_COIN:
					playerCoins += 3;
					SoundsManager::playSound(SoundType::COIN);
					break;
				case BonusType::GOLD_COIN:
					playerCoins += 5;
					SoundsManager::playSound(SoundType::COIN);
					break;
				}
				if (playerCoins >= 100) {
					playerCoins %= 100;
					playerLifes++;
				}
				collidedEntity.kill();
			}
			if (collidedEntity.hasComponent<ElementalTileComponent>()
				&& !collidedEntity.hasComponent<DisableComponent>())
			{
				ElementalType elementalType = collidedEntity.getComponent<ElementalTypeComponent>().elementalType;
				auto& playerElementalTypeComponent = entity.getComponent<PlayerElementalTypeComponent>();
				auto& playerElementalType = playerElementalTypeComponent.playerElementalTypes[elementalType];

				playerElementalType.remainingTime = playerElementalType.maxTime;

				if (collidedEntity.hasComponent<ResetTileComponent>()) {
					collidedEntity.getComponent<ResetTileComponent>().activated = true;
					collidedEntity.addComponent<DisableComponent>();
					collidedEntity.activate();
				}
				else {
					collidedEntity.kill();
					collidedEntity.activate();
				}
			}
		}
		
		// DO NOT REMOVE THE COMPONENT, IT WILL BE REMOVED LATER ON
	}
}