#pragma once

#include "RenderableObject.h"

class BackgroundElement 

{
public:
	BackgroundElement(std::string file, sf::RenderWindow &window);
	~BackgroundElement();

	void render(sf::RenderWindow &window);
	void resize(sf::RenderWindow & window);

	void update(float velocity, float deltaTime, sf::RenderWindow & window, sf::View & view);
	void checkBounds(float velocity, float deltaTime, sf::RenderWindow & window, sf::View & view);

	
private:
	sf::Texture layerTexture;
	sf::Sprite backgroundLayer;
};

