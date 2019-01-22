#pragma 
#include "HelperTileComponent.h"
#include "SizeComponent.h"
#include "PositionComponent.h"
#include <anax/System.hpp>
#include <SFML/Graphics.hpp>

class HelperTileRenderingSystem: public anax::System<anax::Requires<
	HelperTileComponent,
	PositionComponent,
	SizeComponent
	>>
{
public:
	HelperTileRenderingSystem();

	void render(sf::RenderWindow& window);

protected:
	sf::RectangleShape m_helperBackground;
	sf::Text m_helperText;
};

