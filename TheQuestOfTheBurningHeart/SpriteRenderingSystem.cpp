#include "SpriteRenderingSystem.h"
#include "GroundCharacterAnimationComponent.h"
#include "AnimationComponent.h"

SpriteRenderingSystem::SpriteRenderingSystem() 
{
}

void SpriteRenderingSystem::render(sf::RenderTarget& renderTarget)
{
	auto entities = getEntities();
	for (auto& entity : entities) {
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
			entity.getComponent<DrawableComponent>().drawable
		);
		if (sprite) {
			auto& position = entity.getComponent<PositionComponent>().position;

			if (entity.hasComponent<AnimationComponent>()) {
				auto& animationComponent = entity.getComponent<AnimationComponent>();
				auto c = entity.getComponents();
				SpriteBox currentBox = animationComponent.state.spriteBoxes[animationComponent.currentFrame];
				sprite->setPosition(sf::Vector2f(
					position.x + currentBox.offset.x,
					position.y + currentBox.offset.y
				));
			} else {
				sprite->setPosition(position); 
			}

			sf::Vector2f scale = entity.getComponent<DrawableComponent>().scale;
			sf::Vector2f spriteScale = sprite->getScale();
			sprite->setScale(sf::Vector2f(
				scale.x * spriteScale.x,
				scale.y * spriteScale.y
			));
		}
	}
}