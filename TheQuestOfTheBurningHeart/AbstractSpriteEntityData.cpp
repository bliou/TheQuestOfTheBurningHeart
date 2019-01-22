#include "AbstractSpriteEntityData.h"
#include "TexturesManager.h"


AbstractSpriteEntityData::AbstractSpriteEntityData(
	std::string texturePath,
	PhysicType physicType,
	sf::Vector2i entitySize)
	: AbstractEntityData::AbstractEntityData(physicType, entitySize),
	m_texturePath(texturePath)
{
}


AbstractSpriteEntityData::~AbstractSpriteEntityData()
{
}

void AbstractSpriteEntityData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.addComponent<DrawableComponent>().drawable = new sf::Sprite();
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	sprite->setTexture(TexturesManager::getTexture(m_texturePath));
}