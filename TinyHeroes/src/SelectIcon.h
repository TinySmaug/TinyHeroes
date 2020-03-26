#pragma once
#include "SFML/Graphics.hpp"
#include "RenderableObject.h"

class SelectIcon : public RenderableObject
{
public:
	SelectIcon(std::string file);
	~SelectIcon();

	void render();
	sf::FloatRect getRenderableArea() { return body; };

	void setPosition(float xPos, float yPos);
	void setScale(float xScale, float yScale);

	bool containsPoint(sf::Vector2f point) { return hidden ? false : body.contains(point); };

private:
	sf::FloatRect body;
	sf::Sprite icon;
	sf::Texture texture;
};

