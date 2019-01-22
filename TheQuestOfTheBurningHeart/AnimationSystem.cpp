#include "AnimationSystem.h"
#include "ElementalAnimationOffsetComponent.h"

AnimationSystem::AnimationSystem()
	: m_timer(0.1f)
{
}

void AnimationSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& animation = entity.getComponent<AnimationComponent>();
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
			entity.getComponent<DrawableComponent>().drawable
		);

		if (animation.setAnimationTimer) {
			animation.defaultAnimationTimer = animation.state.animationTimer == 0.f 
				? m_timer 
				: animation.state.animationTimer;
			animation.currentAnimationTimer = animation.defaultAnimationTimer;
			animation.setAnimationTimer = false;
		}
		animation.currentAnimationTimer -= elapsedTime;
		if (animation.currentAnimationTimer <= 0.f) {
			animation.currentAnimationTimer = animation.defaultAnimationTimer;
			++animation.currentFrame;
		}

		if (animation.currentFrame >= animation.state.spriteBoxes.size())
		{
			// reset the animation
			animation.reset();
		}

		sf::Vector2u textureSize = sprite->getTexture()->getSize();
		SpriteBox currentBox = animation.state.spriteBoxes[animation.currentFrame];
		
		float offsetY = 0.f;
		if (entity.hasComponent<ElementalAnimationOffsetComponent>()) {
			offsetY = entity.getComponent<ElementalAnimationOffsetComponent>().offset;
		}

		sf::IntRect rect(sf::Vector2i(
			currentBox.position.x,
			currentBox.position.y + offsetY * textureSize.y),
			currentBox.size
		);

		sprite->setTextureRect(rect);
	}
}