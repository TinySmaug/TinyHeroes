#pragma once
#include "BackgroundElement.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include <vector>

class Background : public RenderableObject
{
public:
	Background(std::string file, int layerNum, Renderer &renderer, int depth);
	~Background();

	void render(sf::RenderWindow &window);

	void update(sf::Vector2f playerVelocity, float deltaTime, Renderer &renderer);

public:
	std::vector<BackgroundElement*> background;
};

