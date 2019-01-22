#include "BonusTileData.h"
#include "Helpers.h"
#include "BonusTileComponent.h"
#include "TileComponent.h"
#include "TimedMovementComponent.h"

const std::string BonusTileData::texturePath = "bonusTiles.png";
const std::map<BonusType, sf::Vector2f> BonusTileData::typeOffset = {
	{ BonusType::HEART, sf::Vector2f(0.f, 0.f) },
	{ BonusType::COPPER_COIN, sf::Vector2f(0.f, 0.6f) },
	{ BonusType::SILVER_COIN, sf::Vector2f(0.33f, 0.6f) },
	{ BonusType::GOLD_COIN, sf::Vector2f(0.66f, 0.6f) }
};

const std::map<BonusType, sf::Vector2i> BonusTileData::typeEntitySize = {
	{ BonusType::HEART, sf::Vector2i(45, 38) },
	{ BonusType::COPPER_COIN, sf::Vector2i(26, 26) },
	{ BonusType::SILVER_COIN, sf::Vector2i(26, 26) },
	{ BonusType::GOLD_COIN, sf::Vector2i(26, 26) }
};

const std::map<BonusType, sf::Vector2i> BonusTileData::typeGraphicSize = {
	{ BonusType::HEART, sf::Vector2i(45, 38) },
	{ BonusType::COPPER_COIN, sf::Vector2i(26, 26) },
	{ BonusType::SILVER_COIN, sf::Vector2i(26, 26) },
	{ BonusType::GOLD_COIN, sf::Vector2i(26, 26) }
};

BonusTileData::BonusTileData(
	BonusType bonusType)
	: AbstractSensorTileData::AbstractSensorTileData(
		BonusTileData::texturePath,
		BonusTileData::typeEntitySize.at(bonusType)
	),
	m_offset(BonusTileData::typeOffset.at(bonusType)),
	m_graphicSize(BonusTileData::typeGraphicSize.at(bonusType)),
	m_bonusType(bonusType),
	m_defaultState(true)
{

}

BonusTileData::BonusTileData(
	BonusType bonusType,
	float timedMovementTimer,
	b2Vec2 velocity)
	: AbstractSensorTileData::AbstractSensorTileData(
		BonusTileData::texturePath,
		BonusTileData::typeEntitySize.at(bonusType),
		timedMovementTimer,
		velocity
	),
	m_offset(BonusTileData::typeOffset.at(bonusType)),
	m_graphicSize(BonusTileData::typeGraphicSize.at(bonusType)),
	m_bonusType(bonusType),
	m_defaultState(false)
{
}


BonusTileData::~BonusTileData()
{
}

void BonusTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	position = sf::Vector2f(
		position.x + (tileSize.x - m_entitySize.x) / 2,
		position.y + (tileSize.y - m_entitySize.y) / 2
	);
	AbstractSensorTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData);

	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	sf::Vector2u textSize = sprite->getTexture()->getSize();
	sprite->setTextureRect(sf::IntRect(
		sf::Vector2i(
			(int)(textSize.x * m_offset.x),
			(int)(textSize.y * m_offset.y)
		),
		m_graphicSize
	));
	entity.addComponent<BonusTileComponent>(m_bonusType);

	if (!m_defaultState)
		entity.removeComponent<DefaultStateComponent>();
}
