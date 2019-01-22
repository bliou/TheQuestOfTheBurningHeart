#include "AbstractCharacterData.h"
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "GroundCharacterAnimationComponent.h"
#include "LifeComponent.h"
#include "VelocityComponent.h"
#include "ElementalTypeComponent.h"
#include "Helpers.h"
#include "ElementalAnimationOffsetComponent.h"
#include "LayerLevel.h"

AbstractCharacterData::AbstractCharacterData(
	std::string texturePath,
	PhysicType physicType,
	sf::Vector2i entitySize,
	b2Vec2 velocity,
	const std::map<GroundCharacterState, AnimationStateComponent> animationStates,
	int lifes)
	: AbstractSpriteEntityData::AbstractSpriteEntityData(
		texturePath,
		physicType,
		entitySize
	),
	m_velocity(velocity),
	m_animationStates(animationStates),
	m_lifes(lifes)
{
}


AbstractCharacterData::~AbstractCharacterData()
{
}

void AbstractCharacterData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	position = sf::Vector2f(
		position.x + (tileSize.x - m_entitySize.x) / 2,
		position.y + tileSize.y - m_entitySize.y - 1
	);
	AbstractSpriteEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<CharacterComponent>(m_velocity);
	entity.addComponent<AnimationComponent>().state = m_animationStates.at(GroundCharacterState::IDLE);
	entity.addComponent<CharacterOrientationComponent>();
	entity.addComponent<GroundCharacterStateComponent>();
	entity.addComponent<LifeComponent>(m_lifes);
	entity.addComponent<VelocityComponent>();
	entity.addComponent<GroundCharacterAnimationComponent>().states = m_animationStates;
	entity.addComponent<ElementalAnimationOffsetComponent>();
	
	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::CHARACTER_0;
}