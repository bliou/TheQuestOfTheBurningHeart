#pragma once
#include "PhysicsEntityCategory.h"
#include "CharacterOrientation.h"
#include "Helpers.h"
#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

struct FallingTriggerComponent : anax::Component {
	FallingTriggerComponent(
		b2Body* body,
		sf::Vector2i size)
		: sensorsCount(-1)
	{
		b2PolygonShape leftShape;
		leftShape.SetAsBox(size.x / 4 / B2SCALE, size.y / 8 / B2SCALE, b2Vec2(-size.x / 3 / B2SCALE, size.y / 2 / B2SCALE), 0.f);
		b2FixtureDef leftFixture;
		leftFixture.isSensor = true;
		leftFixture.shape = &leftShape;
		leftFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::FALLING_TRIGGER;
		leftFixture.filter.maskBits = (uint16)PhysicsEntityCategory::TILE;
		leftFixture.userData = (int*)CharacterOrientation::LEFT;
		body->CreateFixture(&leftFixture);

		b2PolygonShape rightShape;
		rightShape.SetAsBox(size.x / 4 / B2SCALE, size.y / 8 / B2SCALE, b2Vec2(size.x / 3 / B2SCALE, size.y / 2 / B2SCALE), 0.f);
		b2FixtureDef rightFixture;
		rightFixture.isSensor = true;
		rightFixture.shape = &rightShape;
		rightFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::FALLING_TRIGGER;
		rightFixture.filter.maskBits = (uint16)PhysicsEntityCategory::TILE;
		rightFixture.userData = (int*)CharacterOrientation::RIGHT;
		body->CreateFixture(&rightFixture);
	}

	int sensorsCount;
};