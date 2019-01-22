#include "GameScreenLoadingThread.h"
#include "FontsManager.h"
#include "Helpers.h"
#include "GameScreen.h"
#include "GameScreenLoadingState.h"


GameScreenLoadingThread::GameScreenLoadingThread(
	GameScreenLoadingState* state,
	GameScreen& gameInstance,
	sf::RenderWindow& window,
	std::string titleContent)
	: m_gameInstance(gameInstance),
	m_window(window),
	m_progress(0.f)
{
	// Configure the title
	m_title.setFont(FontsManager::getFont(Font::CURLZ));
	m_title.setStyle(sf::Text::Bold);
	m_title.setCharacterSize(45);
	m_title.setFillColor(sf::Color::Black);
	m_title.setString(titleContent);

	// Configure the progress content
	m_progressContent.setFont(FontsManager::getFont(Font::CURLZ));
	m_progressContent.setStyle(sf::Text::Bold);
	m_progressContent.setCharacterSize(27);
	m_progressContent.setFillColor(sf::Color::Black);

	// Configure the full progress bar
	m_fullProgressBar.setFillColor(sf::Color::Black);
	m_fullProgressBar.setOutlineColor(sf::Color(108, 110, 158));
	m_fullProgressBar.setOutlineThickness(1.25f);
	m_fullProgressBar.setSize(sf::Vector2f(100.0f, 25.0f));
	m_fullProgressBar.setScale(sf::Vector2f(2.0f, 1.0f));
	sf::FloatRect fullProgressBarRect = m_fullProgressBar.getLocalBounds();
	m_fullProgressBar.setOrigin(
		fullProgressBarRect.left + fullProgressBarRect.width / 2.0f,
		fullProgressBarRect.top + fullProgressBarRect.height / 2.0f
	);
	m_fullProgressBar.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));

	// Configure the progress bar
	m_progressBar.setFillColor(sf::Color(0, 180, 204));
	m_progressBar.setSize(sf::Vector2f(100.0f, 25.0f));
	m_progressBar.setScale(sf::Vector2f(2.0f, 1.0f));
	sf::FloatRect progressBarRect = m_progressBar.getLocalBounds();
	m_progressBar.setOrigin(
		progressBarRect.left + progressBarRect.width / 2.0f,
		progressBarRect.top + progressBarRect.height / 2.0f
	);
	m_progressBar.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));
}


GameScreenLoadingThread::~GameScreenLoadingThread()
{
}

void GameScreenLoadingThread::setProgressContent(
	std::string progressContent)
{
	m_progressContent.setString(progressContent);
}

void GameScreenLoadingThread::setProgress(float progress)
{
	m_progress = progress;
	m_progressBar.setSize(sf::Vector2f(progress, 25.0f));
}

float GameScreenLoadingThread::getProgress() const
{
	return m_progress;
}

void GameScreenLoadingThread::draw()
{
	m_window.clear();
	m_window.setView(m_window.getDefaultView());

	m_state->renderLayer(m_window, m_gameInstance);

	// Displays the progress bar
	m_window.draw(m_fullProgressBar);
	m_window.draw(m_progressBar);

	// Displays the progress content
	sf::FloatRect textRect = m_progressContent.getLocalBounds();
	m_progressContent.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);

	m_progressContent.setPosition(sf::Vector2f(screenSize.x / 2.0f, 2.0f * screenSize.y / 3.0f));

	m_window.draw(m_progressContent);

	// Draw the title
	textRect = m_title.getLocalBounds();
	m_title.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);
	m_title.setPosition(sf::Vector2f(
		(float)screenSize.x / 2.0f,
		(float)screenSize.y / 5.0f)
	);

	m_window.draw(m_title);
	m_window.display();
}