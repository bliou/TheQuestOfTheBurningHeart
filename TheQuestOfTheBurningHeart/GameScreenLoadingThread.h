#pragma once
#include <SFML/Graphics.hpp>

class GameScreen;
class GameScreenLoadingState;

class GameScreenLoadingThread
{
public:
	GameScreenLoadingThread(
		GameScreenLoadingState* state,
		GameScreen& gameInstance,
		sf::RenderWindow& window,
		std::string titleContent);
	~GameScreenLoadingThread();

	void draw();
	void setProgressContent(std::string progressContent);
	void setProgress(float progress);

	float getProgress() const;

protected:
	GameScreen& m_gameInstance;
	GameScreenLoadingState* m_state;
	sf::RenderWindow& m_window;

	float m_progress;

	// Used to display the title of the map
	sf::Text m_title;

	// Used to display the current loading progress
	sf::RectangleShape m_progressBar;
	sf::RectangleShape m_fullProgressBar;
	sf::Text m_progressPercent;
	sf::Text m_progressContent;

};

