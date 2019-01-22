#include "ScreenCollisionSystem.h"
#include "CharacterComponent.h"
#include "MonsterComponent.h"
#include "GamePlayerComponent.h"
#include "CharacterOrientationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "DyingComponent.h"
#include "LifeComponent.h"
#include "GameScreen.h"
#include "GameScreenDeadPlayerState.h"
#include "SoundsManager.h"
#include "MusicsManager.h"
#include "ChickenBossPatternComponent.h"
#include "StartRangeAttackCollisionComponent.h"

ScreenCollisionSystem::ScreenCollisionSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void ScreenCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<CharacterComponent>())
		{
			auto& screenSide = entity.getComponent<ScreenCollisionComponent>().screenSide;

			if (entity.hasComponent<MonsterComponent>())
				monsterScreenCollision(entity, screenSide);

			if (entity.hasComponent<GamePlayerComponent>())
				playerScreenCollision(entity, screenSide);
			
		}

		entity.removeComponent<ScreenCollisionComponent>();
		entity.activate();
	}
}

void ScreenCollisionSystem::monsterScreenCollision(
	anax::Entity& monster,
	ScreenSide screenSide)
{
	auto& orientation = monster.getComponent<CharacterOrientationComponent>().orientation;
	auto& state = monster.getComponent<GroundCharacterStateComponent>().state;
	switch (screenSide)
	{
	case ScreenSide::LEFT_SCREEN:
		orientation = CharacterOrientation::RIGHT;
		if (monster.hasComponent<ChickenBossPatternComponent>()) {
			auto& chickenBossPatternComponent = monster.getComponent<ChickenBossPatternComponent>();
			chickenBossPatternComponent.currentRangeAttackCounter++;
			if (chickenBossPatternComponent.currentRangeAttackCounter >= chickenBossPatternComponent.rangeAttackCounter) {
				monster.addComponent<StartRangeAttackCollisionComponent>().collidedEntityId = m_gameInstance.getPlayerId();
				monster.activate();
				// Add an offset to the monster physic body so it is not in the screen
				b2Body* body = monster.getComponent<PhysicComponent>().body;
				body->SetTransform(b2Vec2(
					body->GetPosition().x + 1.f,
					body->GetPosition().y
				), 0.f);

				chickenBossPatternComponent.currentRangeAttackCounter = 0;
			}
		}
		break;
	case ScreenSide::RIGHT_SCREEN:
		orientation = CharacterOrientation::LEFT;
		if (monster.hasComponent<ChickenBossPatternComponent>()) {
			auto& chickenBossPatternComponent = monster.getComponent<ChickenBossPatternComponent>();
			chickenBossPatternComponent.currentRangeAttackCounter++;
			if (chickenBossPatternComponent.currentRangeAttackCounter >= chickenBossPatternComponent.rangeAttackCounter) {
				monster.addComponent<StartRangeAttackCollisionComponent>().collidedEntityId = m_gameInstance.getPlayerId();
				monster.activate();
				// Add an offset to the monster physic body so it is not in the screen
				b2Body* body = monster.getComponent<PhysicComponent>().body;
				body->SetTransform(b2Vec2(
					body->GetPosition().x - 1.f,
					body->GetPosition().y
				), 0.f);

				chickenBossPatternComponent.currentRangeAttackCounter = 0;
			}
		}
		break;
	case ScreenSide::BOTTOM_SCREEN:
		state = GroundCharacterState::DYING;
		monster.addComponent<DyingComponent>();
		monster.activate();
		break;
	}
}

void ScreenCollisionSystem::playerScreenCollision(
	anax::Entity& player,
	ScreenSide screenSide)
{
	auto& state = player.getComponent<GroundCharacterStateComponent>().state;
	switch (screenSide)
	{
	case ScreenSide::BOTTOM_SCREEN:
		m_gameInstance.killPlayer(player);
		break;
	}
}