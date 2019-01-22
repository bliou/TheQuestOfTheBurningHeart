#pragma once
#include "AbstractShapeEntityData.h"
#include "DialogSide.h"
#include <map>

class DialogData: public AbstractShapeEntityData
{
public:
	DialogData(DialogSide dialogSide);
	~DialogData();

	void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::map<DialogSide, sf::Vector2i> sideSize;

	const DialogSide m_dialogSide;
};

