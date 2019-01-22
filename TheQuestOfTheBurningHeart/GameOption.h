#pragma once

#include <SFML/Graphics.hpp>
#include "FontsManager.h"

template <typename T>
class GameOption
{
public:
	GameOption(
		T,
		std::string,
		int,
		float,
		int);
	~GameOption();

	GameOption(const GameOption&) = delete;
	GameOption& operator=(const GameOption) = delete;

	// Draw the game option to the window
	void Draw(sf::RenderWindow&, bool);

	// Get the option value
	T GetValue() const;

private:
	sf::Text m_text;

	// The value of the option
	T m_value;
	// The options number
	float m_optionsSize;
	// The offset of this option
	int m_offset;
};


template <typename T>
GameOption<T>::GameOption(
	T value,
	std::string content,
	int offset,
	float optionsSize,
	int characterSize)
	: m_text(), m_value(value), m_offset(offset), m_optionsSize(optionsSize)
{
	m_text.setFont(FontsManager::getFont(Font::CURLZ));
	m_text.setString(content);
	m_text.setStyle(sf::Text::Bold);
	m_text.setCharacterSize(characterSize);
	m_text.setFillColor(sf::Color::White);
}

template <typename T>
GameOption<T>::~GameOption()
{
}


template <typename T>
T GameOption<T>::GetValue() const
{
	return m_value;
}

template <typename T>
void GameOption<T>::Draw(sf::RenderWindow& window, bool selected)
{
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);

	if (selected)
		m_text.setFillColor(sf::Color::Red);
	else
		m_text.setFillColor(sf::Color::White);

	sf::Vector2f viewCenter = window.getView().getCenter();
	sf::Vector2f viewSize = window.getView().getSize();
	sf::Vector2f screenOrigin = sf::Vector2f(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

	float split = viewSize.y / m_optionsSize;

	m_text.setPosition(sf::Vector2f(viewSize.x / 2.0f + screenOrigin.x, split / 2.0f + screenOrigin.y + m_offset * split));
	window.draw(m_text);
}
