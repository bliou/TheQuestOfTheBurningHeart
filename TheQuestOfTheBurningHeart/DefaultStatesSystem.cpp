#include "DefaultStatesSystem.h"
#include "PhysicComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"
#include "GroundCharacterStateComponent.h"
#include "SizeComponent.h"
#include "LifeComponent.h"
#include "CharacterOrientationComponent.h"
#include "MonsterComponent.h"
#include "DisableComponent.h"
#include "GamePlayerComponent.h"
#include "MonsterActivatorTriggerComponent.h"
#include "Helpers.h"
#include "RangeAttackPatternComponent.h"
#include "CloseAttackPatternComponent.h"
#include "DefaultPatternComponent.h"
#include "GameScreen.h"

DefaultStatesSystem::DefaultStatesSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void DefaultStatesSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<PositionComponent>()) {
			auto& positionComponent = entity.getComponent<PositionComponent>();
			positionComponent.position = positionComponent.defaultPosition;
		}
		if (entity.hasComponent<SizeComponent>()) {
			auto& sizeComponent = entity.getComponent<SizeComponent>();
			sizeComponent.size = sizeComponent.defaultSize;
		}
		if (entity.hasComponent<CharacterOrientationComponent>()) {
			auto& orientationComponent = entity.getComponent<CharacterOrientationComponent>();
			orientationComponent.orientation = orientationComponent.defaultOrientation;
		}
		if (entity.hasComponent<GroundCharacterStateComponent>()) {
			auto& stateComponent = entity.getComponent<GroundCharacterStateComponent>();
			stateComponent.state = stateComponent.defaultState;
		}
		if (entity.hasComponent<MonsterComponent>()) {
			entity.addComponent<DisableComponent>();
			entity.activate();
			auto& lifeComponent = entity.getComponent<LifeComponent>();
			lifeComponent.lifes = lifeComponent.defaultLifes;
		}
		if (entity.hasComponent<GamePlayerComponent>()) {
			b2Body* body = entity.getComponent<PhysicComponent>().body;
			entity.removeComponent<MonsterActivatorTriggerComponent>();
			entity.addComponent<MonsterActivatorTriggerComponent>(body);
			entity.activate();
		}
		if (entity.hasComponent<VelocityComponent>()) {
			auto& velocityComponent = entity.getComponent<VelocityComponent>();
			velocityComponent.velocity = b2Vec2(0.f, 0.f);
		}
		if (entity.hasComponent<PhysicComponent>()) {
			auto& body = entity.getComponent<PhysicComponent>().body;
			auto& defaultPosition = entity.getComponent<PositionComponent>().defaultPosition;
			auto& defaultSize = entity.getComponent<SizeComponent>().defaultSize;

			float posX = defaultPosition.x + defaultSize.x / 2;
			float posY = defaultPosition.y + defaultSize.y / 2;
			body->SetTransform(
				b2Vec2(posX / B2SCALE, posY / B2SCALE), 
				0.f);
		}
		if (entity.hasComponent<RangeAttackPatternComponent>()) {
			entity.removeComponent<RangeAttackPatternComponent>();
			entity.activate();
		}
		if (entity.hasComponent<CloseAttackPatternComponent>()) {
			entity.removeComponent<CloseAttackPatternComponent>();
			entity.activate();
		}
		if (entity.hasComponent<DefaultPatternComponent>()) {
			std::string patternId = entity.getComponent<DefaultPatternComponent>().patternId;
			m_gameInstance.addPatternToEntity(
				patternId,
				entity.getId().index
			);
			entity.activate();
		}
	}
}