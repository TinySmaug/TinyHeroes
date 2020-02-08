#pragma once
#include "SFML\Graphics.hpp"

class RenderableObject
{
public:
	RenderableObject();
	~RenderableObject();

	virtual void render(sf::RenderWindow &window) = 0;
};

