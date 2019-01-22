#pragma once
#include "GamePlayerComponent.h"
#include "LifeComponent.h"
#include "PlayerCoinsComponent.h"
#include "PlayerElementalTypeComponent.h"
#include <anax/System.hpp>
#include <SFML/Graphics.hpp>

class PlayerDataRenderingSystem: public anax::System<anax::Requires<
	GamePlayerComponent,
	LifeComponent,
	PlayerCoinsComponent,
	PlayerElementalTypeComponent>>
{
public:
	PlayerDataRenderingSystem();

	void render(sf::RenderWindow& window);

protected:
	void renderLifes(sf::RenderWindow& window, int lifes);
	void renderCoins(sf::RenderWindow& window, int coins);
	void renderElemental(
		sf::RenderWindow& window,
		PlayerElementalTypeComponent elementalComponent);

	/// Lifes drawing data
	sf::View m_lifesView;
	sf::Sprite m_lifesSprite;
	sf::Text m_lifesText;

	/// Coins drawing data
	sf::View m_coinsView;
	sf::Sprite m_coinsSprite;
	sf::Text m_coinsText;
	
	/// Elemental draw data
	sf::View m_elementalView;
	sf::Sprite m_elementalSprite;
	sf::RectangleShape m_elementalTotalTime;
	sf::RectangleShape m_elementalRemainingTime;
};

