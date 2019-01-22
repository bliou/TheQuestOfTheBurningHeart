#include "StartEntityCollisionSystem.h"
#include "GamePlayerComponent.h"
#include "MonsterComponent.h"
#include "DisableComponent.h"
#include "GroundCharacterStateComponent.h"
#include "LifeComponent.h"
#include "GameScreen.h"
#include "GameScreenDeadPlayerState.h"
#include "BreakableTileComponent.h"
#include "SoundsManager.h"
#include "MusicsManager.h"

StartEntityCollisionSystem::StartEntityCollisionSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void StartEntityCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<GamePlayerComponent>())
		{
			auto collidedEntitiesId = entity.getComponent<StartEntityCollisionComponent>().collidedEntitiesId;
			for (uint64_t collidedEntityId : collidedEntitiesId)
			{
				anax::Entity collidedEntity = entity.getWorld().getEntity(collidedEntityId);

				if (collidedEntity.hasComponent<MonsterComponent>()
					&& !collidedEntity.hasComponent<DisableComponent>()
					&& collidedEntity.hasComponent<GroundCharacterStateComponent>()) {
					auto& state = collidedEntity.getComponent<GroundCharacterStateComponent>().state;
					if (state != GroundCharacterState::DYING) {
						playerLoseLife(entity);
						MusicsManager::stopMusic();
						SoundsManager::playSound(SoundType::PLAYER_DEATH);
					}
				}

				if (collidedEntity.hasComponent<BreakableTileComponent>()) {
					auto& breakableTileComponent = collidedEntity.getComponent<BreakableTileComponent>();

					sf::Vector2f tilePosition = collidedEntity.getComponent<PositionComponent>().position;
					sf::Vector2i tileSize = collidedEntity.getComponent<SizeComponent>().size;

					sf::Vector2f playerPosition = entity.getComponent<PositionComponent>().position;
					sf::Vector2i playerSize = entity.getComponent<SizeComponent>().size;

					playerPosition.y -= playerSize.y / 2.f;

					if (!breakableTileComponent.broken
						&& playerPosition.y > tilePosition.y + tileSize.y) {
						breakableTileComponent.broken = true;
						if (breakableTileComponent.tileToCreate != "")
							m_gameInstance.addEntityToCreate(
								breakableTileComponent.tileToCreate,
								tilePosition
							);
					}
				}
			}
		}
		entity.removeComponent<StartEntityCollisionComponent>();
		entity.activate();
	}
}

void StartEntityCollisionSystem::playerLoseLife(anax::Entity& player)
{
	m_gameInstance.killPlayer(player);
}