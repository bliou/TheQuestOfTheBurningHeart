#include "AbstractLayerData.h"

const PhysicType AbstractLayerData::physicType = PhysicType::pNone;


AbstractLayerData::AbstractLayerData()
	: AbstractSpriteEntityData::AbstractSpriteEntityData(
		"",
		AbstractLayerData::physicType,
		sf::Vector2i()
	)
{
}


AbstractLayerData::~AbstractLayerData()
{
}

void AbstractLayerData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	m_texturePath = specificData.at("texture").get<std::string>();

	AbstractSpriteEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
}