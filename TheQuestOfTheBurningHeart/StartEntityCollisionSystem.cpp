#include "StartEntityCollisionSystem.h"
#include "GamePlayerComponent.h"
#include "MonsterComponent.h"
#include "DisableComponent.h"
#include "GroundCharacterStateComponent.h"
#include "LifeComponent.h"
#include "GameScreen.h"
#include "GameScreenDeadPlayerState.h"
#include "SoundsManager.h"
#include "MusicsManager.h"
#include "PlayerJumpLoaderComponent.h"

StartEntityCollisionSystem::StartEntityCollisionSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void StartEntityCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto collidedEntitiesId = entity.getComponent<StartEntityCollisionComponent>().collidedEntitiesId;
		for (uint64_t collidedEntityId : collidedEntitiesId)
		{
			anax::Entity collidedEntity = entity.getWorld().getEntity(collidedEntityId);

			if (entity.hasComponent<GamePlayerComponent>())
			{
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
			}
			if (collidedEntity.hasComponent<TileComponent>()
				&& entity.hasComponent<CharacterComponent>()
				&& entity.hasComponent<GroundCharacterStateComponent>())
			{
				sf::Vector2f tilePosition = collidedEntity.getComponent<PositionComponent>().position;
				sf::Vector2i tileSize = collidedEntity.getComponent<SizeComponent>().size;

				sf::Vector2f entityPosition = entity.getComponent<PositionComponent>().position;
				sf::Vector2i entitySize = entity.getComponent<SizeComponent>().size;

				entityPosition.y -= entitySize.y / 2.f;

				if (entityPosition.y > tilePosition.y + tileSize.y)
				{
					auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
					if (state == GroundCharacterState::JUMP)
						state = GroundCharacterState::FALL;

					if (entity.hasComponent<PlayerJumpLoaderComponent>()) {
						entity.removeComponent<PlayerJumpLoaderComponent>();
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