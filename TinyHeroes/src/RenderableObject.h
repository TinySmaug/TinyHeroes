#pragma once
#include "SFML\Graphics.hpp"

class RenderableObject
{
public:
	RenderableObject();
	virtual ~RenderableObject();

	virtual void render(sf::RenderWindow &window) = 0;

	int getDepth() { return depth; };

protected:
	int depth;
};

