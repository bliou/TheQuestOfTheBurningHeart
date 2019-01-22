#include "DialogData.h"
#include "DialogComponent.h"
#include "BlockAnimationTimerComponent.h"
#include "Helpers.h"
#include "LayerLevel.h"

const std::map<DialogSide, sf::Vector2i> DialogData::sideSize = {
	{ DialogSide::FULL, sf::Vector2i(screenSize.x, screenSize.y) },
	{ DialogSide::BOTTOM, sf::Vector2i(screenSize.x - 4, screenSize.y / 4) },
	{ DialogSide::TOP, sf::Vector2i(screenSize.x - 4, screenSize.y / 4) }
};


DialogData::DialogData(
	DialogSide dialogSide)
	: AbstractShapeEntityData::AbstractShapeEntityData(
		DialogData::sideSize.at(dialogSide)
	),
	m_dialogSide(dialogSide)
{
}


DialogData::~DialogData()
{
}

void DialogData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	if (m_dialogSide == DialogSide::BOTTOM) {
		position.y += 3.f * screenSize.y / 4.f;
	}

	AbstractShapeEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	std::string dialogContent = specificData.at("content").get<std::string>();
	std::string dialogTitle = specificData.find("title") != specificData.end()
		? specificData.at("title").get<std::string>()
		: "";
	
	entity.addComponent<DialogComponent>(
		m_dialogSide,
		position, 
		dialogContent,
		dialogTitle
	);
	entity.addComponent<BlockAnimationTimerComponent>();

	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::ACTION_0;

	// If we don't want a full screen dialog,
	// stylish the side dialogs
	if (m_dialogSide != DialogSide::FULL) {
		sf::RectangleShape* shape = dynamic_cast<sf::RectangleShape*>(
			entity.getComponent<DrawableComponent>().drawable
		);
		shape->setFillColor(sf::Color(0, 0, 0, 70));
		shape->setOutlineThickness(2.f);
		shape->setOutlineColor(sf::Color::Black);
		if (m_dialogSide == DialogSide::TOP)
			shape->setPosition(position.x + 2.f, position.y + 2.f);
		else
			shape->setPosition(position.x + 2.f, position.y - 2.f);
	}
}