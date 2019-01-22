#include "ContactsListener.h"
#include "GameScreen.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Collision/b2Collision.h"
#include "PhysicsEntityCategory.h"
#include "CharacterOrientation.h"
#include "TileComponent.h"
#include "StartFootCollisionComponent.h"
#include "EndFootCollisionComponent.h"
#include "StartMonsterSensorCollisionComponent.h"
#include "EndMonsterSensorCollisionComponent.h"
#include "StartFallingSensorCollisionComponent.h"
#include "EndFallingSensorCollisionComponent.h"
#include "ScreenCollisionComponent.h"
#include "StartEntityCollisionComponent.h"
#include "EndEntityCollisionComponent.h"
#include "StartCloseAttackCollisionComponent.h"
#include "EndCloseAttackCollisionComponent.h"
#include "MonsterActivatorCollisionComponent.h"
#include "ProjectileCollisionComponent.h"
#include "GroundCharacterStateComponent.h"
#include "MonsterComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include "DisableComponent.h"
#include "SlopeTileComponent.h"
#include "ContactsHelper.h"

ContactsListener::ContactsListener(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}


ContactsListener::~ContactsListener()
{
}

void ContactsListener::BeginContact(b2Contact* contact) 
{
	b2WorldManifold* worldManifold = new b2WorldManifold();
	contact->GetWorldManifold(worldManifold);

	uint64_t entityAId = (uint64_t)(contact->GetFixtureA()->GetBody()->GetUserData());
	uint64_t entityBId = (uint64_t)(contact->GetFixtureB()->GetBody()->GetUserData());

	anax::Entity* entityA = entityAId >= 0 && entityAId <= 10000
		? &m_gameInstance.getWorld()->getEntity(entityAId)
		: nullptr;
	anax::Entity* entityB = entityBId >= 0 && entityBId <= 10000
		? &m_gameInstance.getWorld()->getEntity(entityBId)
		: nullptr;

	if (entityA && entityA->hasComponent<TileComponent>()) {
		auto& tileComponent = entityA->getComponent<TileComponent>();
		if (tileComponent.isOneSided && ContactsHelper::isOneSidedTile(entityA, entityB))
			return;
	}
	if (entityB && entityB->hasComponent<TileComponent>()) {
		auto& tileComponent = entityB->getComponent<TileComponent>();
		if (tileComponent.isOneSided && ContactsHelper::isOneSidedTile(entityB, entityA))
			return;
	}

	b2Filter fA = contact->GetFixtureA()->GetFilterData();
	b2Filter fB = contact->GetFixtureB()->GetFilterData();
	if (fA.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR
		|| fA.categoryBits == (uint16)PhysicsEntityCategory::FALLING_TRIGGER) {
		if (entityA->hasComponent<CharacterOrientationComponent>()
			&& entityA->hasComponent<MonsterComponent>()) {
			uint64_t characterOrientation = reinterpret_cast<uint64_t>(
				contact->GetFixtureA()->GetUserData()
			);
			CharacterOrientation orientation = entityA->getComponent<CharacterOrientationComponent>().orientation;
			if (orientation == (CharacterOrientation)characterOrientation) {
				if (fA.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR)
					entityA->addComponent<StartMonsterSensorCollisionComponent>().collidedEntityId = entityBId;
				else
					entityA->addComponent<StartFallingSensorCollisionComponent>().collidedEntityId = entityBId;
			}
		}
	}
	else if (fA.categoryBits == (uint16)PhysicsEntityCategory::PLAYER_ACTIVATOR_SENSOR) {
		if (entityB->hasComponent<DisableComponent>()) {
			entityB->addComponent<MonsterActivatorCollisionComponent>();
		}
	}
	else if (fA.categoryBits == (uint16)PhysicsEntityCategory::CLOSE_ATTACK_DETECTION_BOX) {
		entityA->addComponent<StartCloseAttackCollisionComponent>().collidedEntityId = entityBId;
	}
	else if (fA.categoryBits == (uint16)PhysicsEntityCategory::SCREEN) {
		uint64_t screenSide =  reinterpret_cast<uint64_t>(
			contact->GetFixtureA()->GetUserData()
		);
		entityB->addComponent<ScreenCollisionComponent>().screenSide = (ScreenSide)screenSide;
	}
	else if (fA.categoryBits == (uint16)PhysicsEntityCategory::PROJECTILE) {
		entityB->addComponent<ProjectileCollisionComponent>().collidedEntityId = entityAId;
	}

	 if (fB.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR
		|| fB.categoryBits == (uint16)PhysicsEntityCategory::FALLING_TRIGGER) {
		if (entityB->hasComponent<CharacterOrientationComponent>()
			&& entityB->hasComponent<MonsterComponent>()) {
			uint64_t characterOrientation = reinterpret_cast<uint64_t>(
				contact->GetFixtureB()->GetUserData()
			);
			CharacterOrientation orientation = entityB->getComponent<CharacterOrientationComponent>().orientation;
			if (orientation == (CharacterOrientation)characterOrientation) {
				if (fB.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR)
					entityB->addComponent<StartMonsterSensorCollisionComponent>().collidedEntityId = entityAId;
				else
					entityB->addComponent<StartFallingSensorCollisionComponent>().collidedEntityId = entityAId;
			}
		}
	}
	else if (fB.categoryBits == (uint16)PhysicsEntityCategory::PLAYER_ACTIVATOR_SENSOR) {
		if (entityA->hasComponent<DisableComponent>()) {
			entityA->addComponent<MonsterActivatorCollisionComponent>();
		}
	}
	else if (fB.categoryBits == (uint16)PhysicsEntityCategory::CLOSE_ATTACK_DETECTION_BOX) {
		entityB->addComponent<StartCloseAttackCollisionComponent>().collidedEntityId = entityAId;
	}
	else if (fB.categoryBits == (uint16)PhysicsEntityCategory::SCREEN) {
		uint64_t screenSide = reinterpret_cast<uint64_t>(
			contact->GetFixtureB()->GetUserData()
		);
		entityA->addComponent<ScreenCollisionComponent>().screenSide = (ScreenSide)screenSide;
	}
	else if (fB.categoryBits == (uint16)PhysicsEntityCategory::PROJECTILE) {
		entityA->addComponent<ProjectileCollisionComponent>().collidedEntityId = entityBId;
	}

	if (canCollide(fA.categoryBits)
		&& canCollide(fB.categoryBits)) {
		if (!entityA->hasComponent<StartEntityCollisionComponent>()) {
			entityA->addComponent<StartEntityCollisionComponent>().collidedEntitiesId.push_back(entityBId);
		}
		else {
			entityA->getComponent<StartEntityCollisionComponent>().collidedEntitiesId.push_back(entityBId);
		}
		if (!entityB->hasComponent<StartEntityCollisionComponent>()) {
			entityB->addComponent<StartEntityCollisionComponent>().collidedEntitiesId.push_back(entityAId);
		}
		else {
			entityB->getComponent<StartEntityCollisionComponent>().collidedEntitiesId.push_back(entityAId);
		}
	}
	if (entityA)
		entityA->activate();
	if (entityB)
		entityB->activate();
}

void ContactsListener::EndContact(b2Contact* contact)
{
	contact->SetEnabled(true);

	void* entityAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* entityBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	if (reinterpret_cast<int64_t>(entityAUserData) == PhysicComponent::bodyRemoving
		|| reinterpret_cast<int64_t>(entityBUserData) == PhysicComponent::bodyRemoving)
		return;

	uint64_t entityAId = (uint64_t)entityAUserData;
	uint64_t entityBId = (uint64_t)entityBUserData;

	anax::Entity* entityA = entityAId >= 0 && entityAId <= 10000
		? &m_gameInstance.getWorld()->getEntity(entityAId)
		: nullptr;
	anax::Entity* entityB = entityBId >= 0 && entityBId <= 10000
		? &m_gameInstance.getWorld()->getEntity(entityBId)
		: nullptr;

	b2Filter fA = contact->GetFixtureA()->GetFilterData();
	b2Filter fB = contact->GetFixtureB()->GetFilterData();
	if (fA.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR
		|| fA.categoryBits == (uint16)PhysicsEntityCategory::FALLING_TRIGGER) {
		if (entityA->hasComponent<CharacterOrientationComponent>()
			&& entityA->hasComponent<MonsterComponent>()) {
			uint64_t characterOrientation = reinterpret_cast<uint64_t>(
				contact->GetFixtureA()->GetUserData()
			);
			CharacterOrientation orientation = entityA->getComponent<CharacterOrientationComponent>().orientation;
			if (orientation == (CharacterOrientation)characterOrientation) {
				if (fB.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR)
					entityA->addComponent<EndMonsterSensorCollisionComponent>().collidedEntityId = entityBId;
				else
					entityA->addComponent<EndFallingSensorCollisionComponent>().collidedEntityId = entityBId;
			}
		}
	}
	else if (fA.categoryBits == (uint16)PhysicsEntityCategory::CLOSE_ATTACK_DETECTION_BOX) {
		entityA->addComponent<EndCloseAttackCollisionComponent>();
	}

	if (fB.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR
		|| fB.categoryBits == (uint16)PhysicsEntityCategory::FALLING_TRIGGER) {
		if (entityB->hasComponent<CharacterOrientationComponent>()
			&& entityB->hasComponent<MonsterComponent>()) {
			uint64_t characterOrientation = reinterpret_cast<uint64_t>(
				contact->GetFixtureA()->GetUserData()
			);
			CharacterOrientation orientation = entityB->getComponent<CharacterOrientationComponent>().orientation;
			if (orientation == (CharacterOrientation)characterOrientation) {
				if (fB.categoryBits == (uint16)PhysicsEntityCategory::MONSTER_SENSOR)
					entityB->addComponent<EndMonsterSensorCollisionComponent>().collidedEntityId = entityAId;
				else
					entityB->addComponent<EndFallingSensorCollisionComponent>().collidedEntityId = entityAId;
			}
		}
	}
	else if (fB.categoryBits == (uint16)PhysicsEntityCategory::CLOSE_ATTACK_DETECTION_BOX) {
		entityB->addComponent<EndCloseAttackCollisionComponent>();
	}

	if (canCollide(fA.categoryBits)
		&& canCollide(fB.categoryBits)
		&& entityA && entityB) {
		entityA->addComponent<EndEntityCollisionComponent>().collidedEntityId = entityBId;
		entityB->addComponent<EndEntityCollisionComponent>().collidedEntityId = entityAId;
	}
	if (entityA)
		entityA->activate();
	if (entityB)
		entityB->activate();
}

void ContactsListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	uint64_t entityAId = reinterpret_cast<uint64_t>(
		contact->GetFixtureA()->GetBody()->GetUserData()
	);
	uint64_t entityBId = reinterpret_cast<uint64_t>(
		contact->GetFixtureB()->GetBody()->GetUserData()
	);

	anax::Entity* entityA = entityAId >= 0 && entityAId <= 10000
		? &m_gameInstance.getWorld()->getEntity(entityAId)
		: nullptr;
	anax::Entity* entityB = entityBId >= 0 && entityBId <= 10000
		? &m_gameInstance.getWorld()->getEntity(entityBId)
		: nullptr;

	// Check the one sided tiles
	if (entityA && entityA->hasComponent<TileComponent>()) {
		TileComponent tileComponent = entityA->getComponent<TileComponent>();
		if ((tileComponent.isOneSided && ContactsHelper::isOneSidedTile(entityA, entityB))
			|| entityA->hasComponent<DisableComponent>()) {
			contact->SetEnabled(false);
		}
	}
	if (entityB && entityB->hasComponent<TileComponent>()) {
		TileComponent tileComponent = entityB->getComponent<TileComponent>();
		if ((tileComponent.isOneSided && ContactsHelper::isOneSidedTile(entityB, entityA))
			|| entityB->hasComponent<DisableComponent>()) {
			contact->SetEnabled(false);
		}
	}

	b2Filter fA = contact->GetFixtureA()->GetFilterData();
	b2Filter fB = contact->GetFixtureB()->GetFilterData();

	if (entityA && entityA->hasComponent<TileComponent>()
		&& entityB && entityB->hasComponent<CharacterComponent>()) {
		if (fB.categoryBits != (uint16)PhysicsEntityCategory::CHARACTER_FOOT) {
			if (entityB->hasComponent<GroundCharacterStateComponent>()) {
				auto& state = entityB->getComponent<GroundCharacterStateComponent>().state;
				auto& body = entityB->getComponent<PhysicComponent>().body;
				if (body->GetLinearVelocity().y == 0.f
					&& state == GroundCharacterState::FALL)
					contact->SetEnabled(false);
			}
		}
	}
	if (entityB && entityB->hasComponent<TileComponent>()
		&& entityA && entityA->hasComponent<CharacterComponent>()) {
		if (fB.categoryBits != (uint16)PhysicsEntityCategory::CHARACTER_FOOT) {
			if (entityA->hasComponent<GroundCharacterStateComponent>()) {
				auto& state = entityA->getComponent<GroundCharacterStateComponent>().state;
				auto& body = entityA->getComponent<PhysicComponent>().body;
				if (body->GetLinearVelocity().y == 0.f
					&& state == GroundCharacterState::FALL)
					contact->SetEnabled(false);
			}
		}
	}
}

bool ContactsListener::canCollide(uint16 filterBits)
{
	return filterBits == (uint16)PhysicsEntityCategory::MONSTER
		|| filterBits == (uint16)PhysicsEntityCategory::PLAYER
		|| filterBits == (uint16)PhysicsEntityCategory::TILE;
}