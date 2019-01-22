#pragma once
#include "AbstractTileData.h"
#include "BaseTileType.h"

class NoPhysicBlockTileData: public AbstractTileData
{
public:
	NoPhysicBlockTileData(BaseTileType tileType);
	~NoPhysicBlockTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const PhysicType physicType;
	static const sf::Vector2i entitySize;

	const sf::Vector2i m_offset;
	const BaseTileType m_tileType;
};

