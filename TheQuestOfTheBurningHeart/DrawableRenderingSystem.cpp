#include "DrawableRenderingSystem.h"
#include "LayerLevel.h"


DrawableRenderingSystem::DrawableRenderingSystem()
{
}

bool compareDrawablePriority(anax::Entity entity1, anax::Entity entity2)
{
	return entity1.getComponent<DrawableComponent>().layer <
		entity2.getComponent<DrawableComponent>().layer;
}

void DrawableRenderingSystem::render(
	sf::RenderWindow& window,
	uint16 renderElements)
{
	auto entities = getEntities();
	std::sort(entities.begin(), entities.end(), compareDrawablePriority);
	for (auto& entity : entities) {
		int layer = entity.getComponent<DrawableComponent>().layer;
		sf::Drawable* drawable = entity.getComponent<DrawableComponent>().drawable;
		
		if (renderElements & (uint16)RenderElement::FIX_LAYER
			&& layer < (int)LayerLevel::LAYER_1) {
			window.draw(*drawable);
		}
		if (renderElements & (uint16)RenderElement::TILE_LAYER
			&& layer >= (int)LayerLevel::LAYER_1
			&& layer <= (int)LayerLevel::LAYER_4) {
			window.draw(*drawable);
		}
		if (renderElements & (uint16)RenderElement::REST
			&& layer > (int)LayerLevel::LAYER_4) {
			window.draw(*drawable);
		}
	}
}