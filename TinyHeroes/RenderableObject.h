#pragma once
#include "SFML\Graphics.hpp"

class RenderableObject
{
public:
	RenderableObject();
	~RenderableObject();

	virtual void render(sf::RenderWindow &window) = 0;
	virtual void resize(sf::RenderWindow &window) = 0;
};

