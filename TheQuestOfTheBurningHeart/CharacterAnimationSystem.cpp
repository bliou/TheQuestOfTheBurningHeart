#include "CharacterAnimationSystem.h"



CharacterAnimationSystem::CharacterAnimationSystem()
{
}

void CharacterAnimationSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(entity.getComponent<DrawableComponent>().drawable);
		auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;

		sf::IntRect rect = sprite->getTextureRect();

		// Set the origin to the center of the sprite so 
		// when we flipe it, it does not seem jumpy
		sprite->setOrigin(sf::Vector2f(
			rect.width / 2.f,
			rect.height / 2.f
		));

		if (orientation == CharacterOrientation::LEFT)
			sprite->setScale(-1.f, 1.f);
		else
			sprite->setScale(1.f, 1.f);
	}
}
