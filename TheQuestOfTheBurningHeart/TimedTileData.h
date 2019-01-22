#pragma once
#include "AbstractSolidBlockTileData.h"

class TimedTileData: public AbstractSolidBlockTileData
{
public:
	TimedTileData(
		float timer = 2.f,
		bool reset = false,
		float resetTimer = 5.f
	);
	~TimedTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i graphicSize;

	float m_timer;

	bool m_reset;
	float m_resetTimer;
};

