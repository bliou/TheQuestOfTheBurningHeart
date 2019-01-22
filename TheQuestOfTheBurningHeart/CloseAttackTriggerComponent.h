#pragma once
#include "PhysicsEntityCategory.h"
#include "Helpers.h"
#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

struct CloseAttackTriggerComponent: anax::Component {
	CloseAttackTriggerComponent(
		b2Body* body,
		sf::Vector2i size)
	{
		b2PolygonShape detectionBox;
		detectionBox.SetAsBox(size.x / 2 / B2SCALE, size.y / 2 / B2SCALE);
		b2FixtureDef detectionFixture;
		detectionFixture.isSensor = true;
		detectionFixture.shape = &detectionBox;
		detectionFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::CLOSE_ATTACK_DETECTION_BOX;
		detectionFixture.filter.maskBits = (uint16)PhysicsEntityCategory::PLAYER;
		body->CreateFixture(&detectionFixture);
	}
};