#pragma once
#include "AbstractTileData.h"
#include "DecorativeTileType.h"

class DecorativeTileData: public AbstractTileData
{
public:
	DecorativeTileData(DecorativeTileType type);
	~DecorativeTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const PhysicType physicType;
	static const sf::Vector2i entitySize;
};

