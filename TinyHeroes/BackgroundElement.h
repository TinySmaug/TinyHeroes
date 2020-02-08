#pragma once

#include "RenderableObject.h"

class BackgroundElement : public RenderableObject

{
public:
	BackgroundElement(std::string file, sf::RenderWindow &window);
	~BackgroundElement();

	void render(sf::RenderWindow &window);
	void update(sf::Vector2f playerVelocity, float deltaTime, sf::RenderWindow & window, sf::View & view);
	void checkBounds(float velocity, float deltaTime, sf::RenderWindow & window, sf::View & view);
	
private:
	std::vector<sf::Texture*> bgTextureLayers;
	std::vector<sf::Sprite> backgrounds;
};

