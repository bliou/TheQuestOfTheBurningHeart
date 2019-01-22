#include "GroundCharacterStateSystem.h"
#include "DyingComponent.h"
#include "DamagedComponent.h"
#include "MonsterComponent.h"
#include "KillComponent.h"
#include "PlayerJumpLoaderComponent.h"
#include "MonsterDamagedComponent.h"
#include "CharacterOrientationComponent.h"
#include "MonsterDeathComponent.h"
#include "GameScreen.h"

GroundCharacterStateSystem::GroundCharacterStateSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void GroundCharacterStateSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
		auto& footContacts = entity.getComponent<CharacterComponent>().footContacts;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& body = entity.getComponent<PhysicComponent>().body;

		switch (state)
		{
		case GroundCharacterState::IDLE:
		case GroundCharacterState::WALK:
			if (footContacts.size() == 0)
				state = GroundCharacterState::FALL;
			break;
		case GroundCharacterState::JUMP:
			if (body->GetLinearVelocity().y > 0.f
				&& !entity.hasComponent<PlayerJumpLoaderComponent>())
				state = GroundCharacterState::FALL;
			break;
		case GroundCharacterState::FALL:
			velocity.y = 0.f;
			if (footContacts.size() != 0) {
				if (velocity.x == 0.f)
					state = GroundCharacterState::IDLE;
				else
					state = GroundCharacterState::WALK;
			}
			break;
		case GroundCharacterState::DYING:
		{
			velocity = b2Vec2(0.f, 0.f);
			if (entity.hasComponent<MonsterComponent>()) {
				if (entity.getComponent<PhysicComponent>().hasFixtures) {
					b2Fixture* fixture = body->GetFixtureList();
					b2Fixture* nextFixture = nullptr;
					while (fixture != nullptr) {
						nextFixture = fixture->GetNext();
						body->DestroyFixture(fixture);
						fixture = nextFixture;
					}
					body->SetActive(false);

					entity.getComponent<PhysicComponent>().hasFixtures = false;
				}

				auto& dyingComponent = entity.getComponent<DyingComponent>();
				dyingComponent.currentDyingTimer -= elapsedTime;
				if (dyingComponent.currentDyingTimer <= 0) {
					if (entity.hasComponent<MonsterDeathComponent>()) {
						auto& monsterDeathComp = entity.getComponent<MonsterDeathComponent>();
						if (monsterDeathComp.useCurrentPosition)
							m_gameInstance.addEntityToCreate(
								monsterDeathComp.id,
								entity.getComponent<PositionComponent>().position
							);
						else
							m_gameInstance.addEntityToCreate(
								monsterDeathComp.id,
								monsterDeathComp.position
							);
					}
					entity.kill();
					entity.activate();
				}
			}
			break;
		}
		case GroundCharacterState::DAMAGED:
		{
			auto& damagedComponent = entity.getComponent<DamagedComponent>();
			damagedComponent.currentTimer -= elapsedTime;
			if (damagedComponent.currentTimer <= 0) {
				state = GroundCharacterState::WALK;
				damagedComponent.currentTimer = damagedComponent.maxTimer;
			}
			break;
		}
		}
	}
}