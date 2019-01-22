#include "GameScreenInformationState.h"
#include "TexturesManager.h"
#include "InputManager.h"
#include "GameScreen.h"
#include "GameScreenRunningState.h"

GameScreenInformationState::GameScreenInformationState(
	std::string helperContent)
	: m_informationText(),
	m_playText()
{
	m_fullHelper.setTexture(
		TexturesManager::getTexture("fullhelper.png")
	);

	m_informationText.setFillColor(sf::Color::Black);
	m_informationText.setFont(FontsManager::getFont(Font::ARIAL));
	m_informationText.setCharacterSize(40);
	m_informationText.setString(helperContent);
	sf::FloatRect textRect = m_informationText.getLocalBounds();
	m_informationText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);


	m_playText.setFillColor(sf::Color::Black);
	m_playText.setFont(FontsManager::getFont(Font::ARIAL));
	m_playText.setCharacterSize(25);
	m_playText.setString("Press enter to resume...");
	textRect = m_playText.getLocalBounds();
	m_playText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);
}


GameScreenInformationState::~GameScreenInformationState()
{
}

void GameScreenInformationState::update(
	GameScreen& gameScreen,
	float elapsedTime)
{
}

void GameScreenInformationState::updateEvent(GameScreen& gameScreen)
{
	gameScreen.m_playerInputSystem.updateEvent(true);

	if (InputManager::keyPressed(sf::Keyboard::Enter)) {
		gameScreen.getState()->setState(
			gameScreen,
			new GameScreenRunningState()
		);
	}
}

void GameScreenInformationState::draw(
	sf::RenderWindow& window,
	GameScreen& gameScreen)
{
	AbstractGameScreenState::draw(window, gameScreen);

	sf::Vector2f viewCenter = window.getView().getCenter();
	sf::IntRect fullHelperRect = m_fullHelper.getTextureRect();
	m_fullHelper.setPosition(
		viewCenter.x - fullHelperRect.width / 2.f,
		viewCenter.y - fullHelperRect.height / 2.f
	);
	window.draw(m_fullHelper);
	m_informationText.setPosition(viewCenter);
	window.draw(m_informationText);
	sf::FloatRect textRect = m_playText.getLocalBounds();
	sf::Vector2f pos = m_fullHelper.getPosition();
	m_playText.setPosition(
		pos.x + fullHelperRect.width - textRect.width,
		pos.y + fullHelperRect.height - 10.f - textRect.height
	);
	window.draw(m_playText);
}

void GameScreenInformationState::renderSystems(
	GameScreen& gameScreen,
	sf::RenderWindow& window)
{
	gameScreen.m_fixLayerRenderingSystem.render(window);
	gameScreen.m_drawableRenderingSystem.render(
		window, 
		(uint16)RenderElement::FIX_LAYER
	);
}