#pragma once
#include "AbstractTileData.h"
#include "SlopeType.h"
#include "BaseTileType.h"

class AbstractSlopeTileData: public AbstractTileData
{
public:
	AbstractSlopeTileData(
		SlopeType slopeType,
		BaseTileType tileType,
		std::map<SlopeType, PhysicType> typePhysic);
	~AbstractSlopeTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const std::string texture;
	static const sf::Vector2i entitySize;

	static const std::map<SlopeType, sf::Vector2i> typeGraphicBox;

	sf::Vector2i m_graphicBox;
	SlopeType m_slopeType;
};

