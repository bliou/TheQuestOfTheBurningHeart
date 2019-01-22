#pragma once
#include "AbstractSensorTileData.h"
#include "BonusType.h"
#include <map>

class BonusTileData: public AbstractSensorTileData
{
public:
	BonusTileData(
		BonusType bonusType
	);
	BonusTileData(
		BonusType bonusType,
		float timedMovementTimer,
		b2Vec2 velocity);
	~BonusTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const std::map<BonusType, sf::Vector2f> typeOffset;
	static const std::map<BonusType, sf::Vector2i> typeEntitySize;
	static const std::map<BonusType, sf::Vector2i> typeGraphicSize;

	const sf::Vector2f m_offset;
	const sf::Vector2i m_graphicSize;
	const BonusType m_bonusType;
	const bool m_defaultState;
};

