#pragma once
#include "PositionComponent.h"
#include "SizeComponent.h"
#include "CharacterComponent.h"
#include "SlopeTileComponent.h"

#include <SFML/Graphics.hpp>
#include <anax/Entity.hpp>

class ContactsHelper
{
public:
	ContactsHelper();

	// http://www.iforce2d.net/b2dtut/one-way-walls
	static bool isOneSidedTile(
		anax::Entity* tile,
		anax::Entity* entity)
	{
		sf::Vector2f tilePosition = tile->getComponent<PositionComponent>().position;
		sf::Vector2f entityPosition = entity->getComponent<PositionComponent>().position;
		sf::Vector2i entitySize = entity->getComponent<SizeComponent>().size;

		if (entity->hasComponent<CharacterComponent>()) {
			entityPosition.y -= entitySize.y / 2.f;
		}

		bool isSlopeTile = tile->hasComponent<SlopeTileComponent>();
		if (isSlopeTile) {
			sf::Vector2i tileSize = tile->getComponent<SizeComponent>().size;
			SlopeType slopeType = tile->getComponent<SlopeTileComponent>().slopeType;
			if (slopeType == SlopeType::SLOPE_UP) {
				return !isLeft(
					sf::Vector2f(tilePosition.x + tileSize.x, tilePosition.y),
					sf::Vector2f(tilePosition.x, tilePosition.y + tileSize.y),
					sf::Vector2f(entityPosition.x + entitySize.x / 2.f, entityPosition.y + entitySize.y / 2.f)
				);
			}
			else {
				return entityPosition.y + entitySize.y / 2.f > tilePosition.y;
			}
		}
		else {
			return entityPosition.y + entitySize.y / 2.f > tilePosition.y;
		}
	}

protected:
	static bool isLeft(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
		return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
	}
};

