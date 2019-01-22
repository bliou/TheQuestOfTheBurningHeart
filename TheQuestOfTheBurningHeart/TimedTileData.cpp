#include "TimedTileData.h"
#include "TileComponent.h"
#include "TimedTileComponent.h"

const std::string TimedTileData::texturePath = "smallTiles.png";
const sf::Vector2i TimedTileData::graphicSize = sf::Vector2i(64, 18);

TimedTileData::TimedTileData(
	float timer,
	bool reset,
	float resetTimer)
	: AbstractSolidBlockTileData::AbstractSolidBlockTileData(
		TimedTileData::texturePath
	),
	m_timer(timer),
	m_reset(reset),
	m_resetTimer(resetTimer)
{
}


TimedTileData::~TimedTileData()
{
}

void TimedTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSolidBlockTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	sprite->setTextureRect(sf::IntRect(
		sf::Vector2i(0, 0),
		TimedTileData::graphicSize
	));
	entity.getComponent<TileComponent>().isOneSided = true;

	if (specificData.find("timedTile") != specificData.end()) {
		m_timer = specificData.at("timedTile").at("timer");
	}
	entity.addComponent<TimedTileComponent>(m_timer);

	if (specificData.find("resetTile") != specificData.end()) {
		m_reset = specificData.at("resetTile").at("reset");
		m_resetTimer = specificData.at("resetTile").at("resetTimer");
	}

	if (m_reset)
		entity.addComponent<ResetTileComponent>(m_resetTimer);
}