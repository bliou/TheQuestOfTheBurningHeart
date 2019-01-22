#include "ElementalTileData.h"
#include "Helpers.h"
#include "ElementalTypeComponent.h"
#include "ElementalTileComponent.h"
#include "ElementalAnimationOffsetComponent.h"
#include "AnimationComponent.h"
#include "AnimationStateComponent.h"
#include "ResetTileComponent.h"

const std::string ElementalTileData::texturePath = "elementalTiles.png";
const sf::Vector2i ElementalTileData::entitySize = sf::Vector2i(32, 32);
const AnimationStateComponent ElementalTileData::animationState(
	std::vector<SpriteBox> {
		SpriteBox(
			sf::Vector2i(0, 0),
			sf::Vector2i(29, 32)
		),
		SpriteBox(
			sf::Vector2i(0, 0),
			sf::Vector2i(29, 32)
		),
		SpriteBox(
			sf::Vector2i(0, 0),
			sf::Vector2i(29, 32)
		)
	}
);
const std::map<ElementalType, float> ElementalTileData::typeGraphicOffset{
	{ ElementalType::FIRE, 0.f }
};

ElementalTileData::ElementalTileData(
	ElementalType elementalType,
	bool reset,
	float resetTimer)
	: AbstractSensorTileData::AbstractSensorTileData(
		ElementalTileData::texturePath,
		ElementalTileData::entitySize
	),
	m_elementalType(elementalType),
	m_reset(reset),
	m_resetTimer(resetTimer)
{
}


ElementalTileData::~ElementalTileData()
{
}

void ElementalTileData::initializeEntity(
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
		specificData
	);

	if (specificData.find("resetTile") != specificData.end()) {
		m_reset = specificData.at("resetTile").at("reset");
		m_resetTimer = specificData.at("resetTile").at("resetTimer");
	}

	entity.addComponent<ElementalTileComponent>();
	entity.addComponent<ElementalTypeComponent>(m_elementalType);
	entity.addComponent<ElementalAnimationOffsetComponent>().offset = typeGraphicOffset.at(m_elementalType);
	entity.addComponent<AnimationComponent>().state = ElementalTileData::animationState;

	if (m_reset)
		entity.addComponent<ResetTileComponent>(m_resetTimer);
}