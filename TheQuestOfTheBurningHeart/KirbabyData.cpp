#include "KirbabyData.h"

const PhysicType KirbabyData::physicType = PhysicType::pNone;


KirbabyData::KirbabyData()
	: AbstractPlayerData::AbstractPlayerData()
{
}


KirbabyData::~KirbabyData()
{
}

void KirbabyData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	m_physicType = KirbabyData::physicType;
	position.x += m_entitySize.x / 2;
	position.y += m_entitySize.y / 2;

	AbstractPlayerData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<AnimationIdComponent>().id = "kirbaby";

	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	entity.getComponent<DrawableComponent>().scale = sf::Vector2f(
		.75f,
		.75f
	);
}