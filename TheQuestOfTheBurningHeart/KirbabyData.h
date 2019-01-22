#pragma once
#include "AbstractPlayerData.h"

class KirbabyData: public AbstractPlayerData
{
public:
	KirbabyData();
	~KirbabyData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const PhysicType physicType;
};

