#include "CharacterFootAdjustmentSystem.h"
#include "PhysicsEntityCategory.h"
#include "StartFootCollisionComponent.h"
#include "EndFootCollisionComponent.h"
#include "TileComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include "SlopeTileComponent.h"
#include "GroupComponent.h"
#include "ContactsHelper.h"
#include <algorithm>

CharacterFootAdjustmentSystem::CharacterFootAdjustmentSystem()
{
}

void CharacterFootAdjustmentSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		b2Body* body = entity.getComponent<PhysicComponent>().body;
		b2ContactEdge* contact = body->GetContactList();

		std::vector<uint64_t> footsId;

		while (contact != nullptr) {
			if (contact->contact->IsTouching())
			{
				void* entityAUserData = contact->contact->GetFixtureA()->GetBody()->GetUserData();
				void* entityBUserData = contact->contact->GetFixtureB()->GetBody()->GetUserData();

				uint64_t entityAId = (uint64_t)entityAUserData;
				uint64_t entityBId = (uint64_t)entityBUserData;

				anax::Entity* entityA = entityAId >= 0 && entityAId <= 10000
					? &entity.getWorld().getEntity(entityAId)
					: nullptr;
				anax::Entity* entityB = entityBId >= 0 && entityBId <= 10000
					? &entity.getWorld().getEntity(entityBId)
					: nullptr;

				b2Filter fA = contact->contact->GetFixtureA()->GetFilterData();
				b2Filter fB = contact->contact->GetFixtureB()->GetFilterData();
				if (fA.categoryBits == (uint16)PhysicsEntityCategory::CHARACTER_FOOT) {
					if (entityB
						&& !(entityB->hasComponent<TileComponent>()
							&& entityB->getComponent<TileComponent>().isOneSided
							&& ContactsHelper::isOneSidedTile(entityB, entityA))) {
						footsId.push_back(entityBId);
					}
				}
				else if (fB.categoryBits == (uint16)PhysicsEntityCategory::CHARACTER_FOOT) {
					if (entityA
						&& !(entityA->hasComponent<TileComponent>()
							&& entityA->getComponent<TileComponent>().isOneSided
							&& ContactsHelper::isOneSidedTile(entityA, entityB))) {
						footsId.push_back(entityAId);
					}
				}
			}
			contact = contact->next;
		}

		std::sort(footsId.begin(), footsId.end());

		auto footContacts = entity.getComponent<CharacterComponent>().footContacts;
		std::sort(footContacts.begin(), footContacts.end());

		auto footIdIt = footsId.begin();
		auto footContactsIt = footContacts.begin();

		while (footContactsIt != footContacts.end()
			&& footIdIt != footsId.end()) {
			if (*footIdIt < *footContactsIt) {
				if (entity.hasComponent<StartFootCollisionComponent>()) {
					entity.getComponent<StartFootCollisionComponent>().collidedEntitiesId.push_back(*footIdIt);
				}
				else {
					entity.addComponent<StartFootCollisionComponent>().collidedEntitiesId.push_back(*footIdIt);
				}
				++footIdIt;
			}
			else if (*footIdIt == *footContactsIt) {
				++footIdIt;
				++footContactsIt;
			}
			else {
				if (entity.hasComponent<EndFootCollisionComponent>()) {
					entity.getComponent<EndFootCollisionComponent>().collidedEntitiesId.push_back(*footContactsIt);
				}
				else {
					entity.addComponent<EndFootCollisionComponent>().collidedEntitiesId.push_back(*footContactsIt);
				}
				++footContactsIt;
			}
		}

		if (footContactsIt == footContacts.end()) {
			while (footIdIt != footsId.end()) {
				if (entity.hasComponent<StartFootCollisionComponent>()) {
					entity.getComponent<StartFootCollisionComponent>().collidedEntitiesId.push_back(*footIdIt);
				}
				else {
					entity.addComponent<StartFootCollisionComponent>().collidedEntitiesId.push_back(*footIdIt);
				}
				++footIdIt;
			}
		}
		else {
			if (footIdIt == footsId.end()) {
				while (footContactsIt != footContacts.end()) {
					if (entity.hasComponent<EndFootCollisionComponent>()) {
						entity.getComponent<EndFootCollisionComponent>().collidedEntitiesId.push_back(*footContactsIt);
					}
					else {
						entity.addComponent<EndFootCollisionComponent>().collidedEntitiesId.push_back(*footContactsIt);
					}
					++footContactsIt;
				}
			}
		}
		entity.activate();
	}
}