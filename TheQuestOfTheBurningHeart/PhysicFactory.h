#pragma once
#include "PhysicType.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

class PhysicFactory
{
public:
	PhysicFactory();
	~PhysicFactory();

	b2Body* createSolidBlockTile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createSensorBlockTile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createSolidSlopeUpTile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createSolidSlopeDownTile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createSensorSlopeUpTile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createSensorSlopeDownTile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createPlayer(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createBodySensorsMonster(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createProjectile(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity);

	b2Body* createBody(
		PhysicType physicType,
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity);
		 
private:
	b2Body* createDynamicBoxBody(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createKinematicBoxBody(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	b2Body* createMonsterBody(
		b2World& world,
		sf::Vector2f position,
		sf::Vector2i size,
		anax::Entity& entity
	);

	sf::Vector2i groupNumber(anax::Entity& entity);
};

