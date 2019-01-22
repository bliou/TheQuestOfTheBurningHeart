#pragma once
#include "PhysicFactory.h"
#include <Box2D/Box2D.h>
#include <anax/anax.hpp>
#include <map>

struct PhysicComponent : anax::Component
{
	PhysicComponent()
		: body(nullptr), 
		hasFixtures(true)
	{
	};
	
	~PhysicComponent() 
	{
		if (body) {
			body->SetUserData((int64_t*)PhysicComponent::bodyRemoving);
			body->GetWorld()->DestroyBody(body);
		}
	}

	void initialize(
		anax::Entity& entity,
		sf::Vector2f position,
		sf::Vector2i size,
		b2World& world,
		PhysicType physicType)
	{
		PhysicFactory factory = PhysicFactory();
		body = factory.createBody(
			physicType, 
			world, 
			position, 
			size,
			entity);
	}

	b2Body* body;
	bool hasFixtures;

	static const int64_t bodyRemoving = -1;
};