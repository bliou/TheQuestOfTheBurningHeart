#pragma once
#include "AbstractScreen.h"
#include "GameOption.h"

class CreditsScreen: public AbstractScreen
{
public:
	CreditsScreen();
	~CreditsScreen();

	virtual int run(sf::RenderWindow& window);

private:
	void update(float elapsedTime);
	void draw(sf::RenderWindow& window);

	// Data for the credits
	sf::Text m_gameByLabel;
	sf::Text m_gameBy;
	sf::Text m_gameMadeWithLabel;
	sf::Text m_gameMadeWith;
	sf::Text m_thanksToLabel;
	sf::Text m_thanksTo;

	sf::Text m_leaveCredits;

	/// Is set to true if we want to scroll the texts
	bool m_scroll;
};