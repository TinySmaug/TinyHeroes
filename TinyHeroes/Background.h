#pragma once
#include "BackgroundElement.h"
#include <vector>

class Background : public RenderableObject
{
public:
	Background(std::string file, int layerNum, sf::RenderWindow &window);
	~Background();

	void render(sf::RenderWindow &window);
	void resize(sf::RenderWindow & window);

	void update(sf::Vector2f playerVelocity, float deltaTime, sf::RenderWindow & window, sf::View & view);

public:
	std::vector<BackgroundElement*> background;
};

