#include "PhysicFactory.h"
#include "GroupComponent.h"
#include "Helpers.h"
#include "PhysicsEntityCategory.h"
#include "PhysicsEntityCategoryHelper.h"
#include "CharacterOrientation.h"

PhysicFactory::PhysicFactory()
{
}


PhysicFactory::~PhysicFactory()
{
}

b2Body* PhysicFactory::createBody(
	PhysicType physicType,
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity) 
{
	switch (physicType)
	{
	case PhysicType::pMonster:
		return createBodySensorsMonster(world, position, size, entity);
	case PhysicType::pPlayer:
		return createPlayer(world, position, size, entity);
	case PhysicType::pSensorBlockTile:
		return createSensorBlockTile(world, position, size, entity);
	case PhysicType::pSensorSlopeDownTile:
		return createSensorSlopeDownTile(world, position, size, entity);
	case PhysicType::pSensorSlopeUpTile:
		return createSensorSlopeUpTile(world, position, size, entity);
	case PhysicType::pSolidBlockTile:
		return createSolidBlockTile(world, position, size, entity);
	case PhysicType::pSolidSlopeDownTile:
		return createSolidSlopeDownTile(world, position, size, entity);
	case PhysicType::pSolidSlopeUpTile:
		return createSolidSlopeUpTile(world, position, size, entity);
	case PhysicType::pProjectile:
		return createProjectile(world, position, size, entity);
	default:
		throw std::exception("Not implemented physic type");
	}
}


b2Body* PhysicFactory::createSolidBlockTile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{

	sf::Vector2i groupNumber = PhysicFactory::groupNumber(entity);
	size.x = size.x * groupNumber.x;
	size.y = size.y * groupNumber.y;
	b2Body* body = createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);

	b2PolygonShape shape;
	shape.SetAsBox(size.x / 2 / B2SCALE, size.y / 2 / B2SCALE, b2Vec2(0, 0), 0.f);

	b2FixtureDef fixture;
	fixture.density = 0.f;
	fixture.friction = 0.f;
	fixture.shape = &shape;
	fixture.filter.categoryBits = (uint16)PhysicsEntityCategory::TILE;
	fixture.filter.maskBits = PhysicsEntityCategoryHelper::solidTileMaskBits;
	fixture.isSensor = false;
	body->CreateFixture(&fixture);

	return body;
}

b2Body* PhysicFactory::createSensorBlockTile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);

	b2PolygonShape shape;
	shape.SetAsBox(size.x / 2 / B2SCALE, size.y / 2 / B2SCALE, b2Vec2(0, 0), 0.f);

	b2FixtureDef fixture;
	fixture.density = 0.f;
	fixture.friction = 0.f;
	fixture.shape = &shape;
	fixture.filter.categoryBits = (uint16)PhysicsEntityCategory::TILE;
	fixture.filter.maskBits = PhysicsEntityCategoryHelper::sensorTileMaskBits;
	fixture.isSensor = true;
	body->CreateFixture(&fixture);

	return body;
}

b2Body* PhysicFactory::createSolidSlopeUpTile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = PhysicFactory::createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);
	b2Vec2 vertices[3];
	sf::Vector2i groupNumber = PhysicFactory::groupNumber(entity);

	vertices[0] = b2Vec2(-size.x / 2 / B2SCALE, size.y / 2 / B2SCALE);
	vertices[1] = b2Vec2(
		(groupNumber.x * size.x) / 2 / B2SCALE + ((groupNumber.x - 1) * size.x) / 2 / B2SCALE,
		-(groupNumber.y * size.y) / 2 / B2SCALE - ((groupNumber.y - 1) * size.y) / 2 / B2SCALE);
	vertices[2] = b2Vec2(
		(groupNumber.x * size.x) / 2 / B2SCALE + ((groupNumber.x - 1) * size.x) / 2 / B2SCALE,
		size.y / 2 / B2SCALE);

	b2PolygonShape shape;
	shape.Set(vertices, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = false;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::TILE;
	fixtureDef.filter.maskBits = PhysicsEntityCategoryHelper::solidTileMaskBits;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* PhysicFactory::createSolidSlopeDownTile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = PhysicFactory::createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);
	b2Vec2 vertices[3];
	sf::Vector2i groupNumber = PhysicFactory::groupNumber(entity);

	vertices[0] = b2Vec2(-size.x / 2 / B2SCALE, -size.y / 2 / B2SCALE);
	vertices[1] = b2Vec2(
		-size.x / 2 / B2SCALE,
		(groupNumber.y * size.y) / 2 / B2SCALE + ((groupNumber.y - 1) * size.y) / 2 / B2SCALE);
	vertices[2] = b2Vec2(
		(groupNumber.x * size.x) / 2 / B2SCALE + ((groupNumber.x - 1) * size.x) / 2 / B2SCALE,
		(groupNumber.y * size.y) / 2 / B2SCALE + ((groupNumber.y - 1) * size.y) / 2 / B2SCALE);


	b2PolygonShape shape;
	shape.Set(vertices, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = false;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::TILE;
	fixtureDef.filter.maskBits = PhysicsEntityCategoryHelper::solidTileMaskBits;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* PhysicFactory::createSensorSlopeUpTile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = PhysicFactory::createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);
	b2Vec2 vertices[3];
	sf::Vector2i groupNumber = PhysicFactory::groupNumber(entity);

	vertices[0] = b2Vec2(-size.x / 2 / B2SCALE, size.y / 2 / B2SCALE);
	vertices[1] = b2Vec2(
		(groupNumber.x * size.x) / 2 / B2SCALE + ((groupNumber.x - 1) * size.x) / 2 / B2SCALE,
		-(groupNumber.y * size.y) / 2 / B2SCALE - ((groupNumber.y - 1) * size.y) / 2 / B2SCALE);
	vertices[2] = b2Vec2(
		(groupNumber.x * size.x) / 2 / B2SCALE + ((groupNumber.x - 1) * size.x) / 2 / B2SCALE,
		size.y / 2 / B2SCALE);


	b2PolygonShape shape;
	shape.Set(vertices, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::TILE;
	fixtureDef.filter.maskBits = PhysicsEntityCategoryHelper::sensorTileMaskBits;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* PhysicFactory::createSensorSlopeDownTile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = PhysicFactory::createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);
	b2Vec2 vertices[3];
	sf::Vector2i groupNumber = PhysicFactory::groupNumber(entity);

	vertices[0] = b2Vec2(-size.x / 2 / B2SCALE, -size.y / 2 / B2SCALE);
	vertices[1] = b2Vec2(
		-size.x / 2 / B2SCALE,
		(groupNumber.y * size.y) / 2 / B2SCALE + ((groupNumber.y - 1) * size.y) / 2 / B2SCALE);
	vertices[2] = b2Vec2(
		(groupNumber.x * size.x) / 2 / B2SCALE + ((groupNumber.x - 1) * size.x) / 2 / B2SCALE,
		(groupNumber.y * size.y) / 2 / B2SCALE + ((groupNumber.y - 1) * size.y) / 2 / B2SCALE);

	b2PolygonShape shape;
	shape.Set(vertices, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.f;
	fixtureDef.friction = 0.f;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::TILE;
	fixtureDef.filter.maskBits = PhysicsEntityCategoryHelper::sensorTileMaskBits;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* PhysicFactory::createPlayer(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = createDynamicBoxBody(
		world,
		position,
		size,
		entity
	);

	b2PolygonShape shape;
	shape.SetAsBox((size.x / 2) / B2SCALE, (size.y / 2) / B2SCALE, b2Vec2(0.f, 0.f), 0.f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.f;
	fixtureDef.shape = &shape;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::PLAYER;
	fixtureDef.filter.maskBits = (uint16)PhysicsEntityCategory::TILE
		| (uint16)PhysicsEntityCategory::MONSTER
		| (uint16)PhysicsEntityCategory::SCREEN
		| (uint16)PhysicsEntityCategory::CLOSE_ATTACK_DETECTION_BOX
		| (uint16)PhysicsEntityCategory::PROJECTILE;
	body->CreateFixture(&fixtureDef);

	b2PolygonShape footShape;
	footShape.SetAsBox(((size.x - 2) / 2) / B2SCALE, (size.y / 4) / B2SCALE, b2Vec2(0.f, 3.f * size.y / 4.f / B2SCALE), 0.f);
	b2FixtureDef footFixture;
	footFixture.isSensor = true;
	footFixture.shape = &footShape;
	footFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::CHARACTER_FOOT;
	footFixture.filter.maskBits = (uint16)PhysicsEntityCategory::TILE
		| (uint16)PhysicsEntityCategory::MONSTER
		| (uint16)PhysicsEntityCategory::SCREEN;
	body->CreateFixture(&footFixture);

	return body;
}

b2Body* PhysicFactory::createBodySensorsMonster(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = createMonsterBody(
		world,
		position,
		size,
		entity
	);

	b2PolygonShape leftShape;
	leftShape.SetAsBox(size.x / 4 / B2SCALE, size.y / 4 / B2SCALE, b2Vec2(-size.x / 3 / B2SCALE, -size.y / 4 / B2SCALE), 0.f);
	b2FixtureDef leftFixture;
	leftFixture.isSensor = true;
	leftFixture.shape = &leftShape;
	leftFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::MONSTER_SENSOR;
	leftFixture.filter.maskBits = (uint16)PhysicsEntityCategory::TILE;
	leftFixture.userData = (int*)CharacterOrientation::LEFT;
	body->CreateFixture(&leftFixture);

	b2PolygonShape rightShape;
	leftShape.SetAsBox(size.x / 4 / B2SCALE, size.y / 4 / B2SCALE, b2Vec2(size.x / 3 / B2SCALE, -size.y / 4 / B2SCALE), 0.f);
	b2FixtureDef rightFixture;
	rightFixture.isSensor = true;
	rightFixture.shape = &leftShape;
	rightFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::MONSTER_SENSOR;
	rightFixture.filter.maskBits = (uint16)PhysicsEntityCategory::TILE;
	rightFixture.userData = (int*)CharacterOrientation::RIGHT;
	body->CreateFixture(&rightFixture);
	
	return body;
}

b2Body* PhysicFactory::createProjectile(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = createKinematicBoxBody(
		world,
		position,
		size,
		entity
	);

	b2PolygonShape shape;
	shape.SetAsBox((size.x / 2) / B2SCALE, (size.y / 2) / B2SCALE, b2Vec2(0.f, 0.f), 0.f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::PROJECTILE;
	fixtureDef.filter.maskBits = (uint16)PhysicsEntityCategory::TILE
		| (uint16)PhysicsEntityCategory::PLAYER;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* PhysicFactory::createDynamicBoxBody(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2BodyDef bodyDef;
	float posX = position.x + size.x / 2;
	float posY = position.y + size.y / 2;
	bodyDef.position = b2Vec2(posX / B2SCALE, posY / B2SCALE);
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.fixedRotation = true;
	b2Body* body = world.CreateBody(&bodyDef);
	body->SetUserData((int*)entity.getId().index);

	return body;
}

b2Body* PhysicFactory::createKinematicBoxBody(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2BodyDef bodyDef;
	float posX = position.x + size.x / 2;
	float posY = position.y + size.y / 2;
	bodyDef.position = b2Vec2(posX / B2SCALE, posY / B2SCALE);
	bodyDef.type = b2BodyType::b2_kinematicBody;
	bodyDef.fixedRotation = true;
	b2Body* body = world.CreateBody(&bodyDef);
	body->SetUserData((int*)entity.getId().index);

	return body;
}

b2Body* PhysicFactory::createMonsterBody(
	b2World& world,
	sf::Vector2f position,
	sf::Vector2i size,
	anax::Entity& entity)
{
	b2Body* body = createDynamicBoxBody(
		world,
		position,
		size,
		entity
	);

	b2PolygonShape shape;
	shape.SetAsBox((size.x / 2) / B2SCALE, (size.y / 2) / B2SCALE, b2Vec2(0.f, 0.f), 0.f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.f;
	fixtureDef.shape = &shape;
	fixtureDef.filter.categoryBits = (uint16)PhysicsEntityCategory::MONSTER;
	fixtureDef.filter.maskBits = (uint16)PhysicsEntityCategory::PLAYER
		| (uint16)PhysicsEntityCategory::TILE
		| (uint16)PhysicsEntityCategory::SCREEN
		| (uint16)PhysicsEntityCategory::PLAYER_ACTIVATOR_SENSOR
		| (uint16)PhysicsEntityCategory::CHARACTER_FOOT;
	body->CreateFixture(&fixtureDef);

	b2PolygonShape footShape;
	footShape.SetAsBox(((size.x - 2) / 2) / B2SCALE, (size.y / 4) / B2SCALE, b2Vec2(0.f, 3.f * size.y / 4.f / B2SCALE), 0.f);
	b2FixtureDef footFixture;
	footFixture.isSensor = true;
	footFixture.shape = &footShape;
	footFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::CHARACTER_FOOT;
	footFixture.filter.maskBits = (uint16)PhysicsEntityCategory::TILE;
	body->CreateFixture(&footFixture);

	return body;
}

sf::Vector2i PhysicFactory::groupNumber(anax::Entity& entity)
{
	int widthNumber = 1;
	int heightNumber = 1;
	if (entity.hasComponent<GroupComponent>()) {
		auto& group = entity.getComponent<GroupComponent>();
		widthNumber = group.widthNumber;
		heightNumber = group.heightNumber;
	}
	return sf::Vector2i(widthNumber, heightNumber);
}