#pragma once
#include "SFML/Graphics.hpp"
#include "RenderableObject.h"

class SelectIcon : public RenderableObject
{
public:
	SelectIcon(std::string file);
	~SelectIcon();

	void render();
	sf::FloatRect getRenderableArea() { return m_body; };

	void setPosition(float xPos, float yPos);
	void setScale(float xScale, float yScale);

	bool containsPoint(sf::Vector2f point) { return m_hidden ? false : m_body.contains(point); };

private:
	sf::FloatRect m_body;
	sf::Sprite m_icon;
	sf::Texture m_texture;
};

