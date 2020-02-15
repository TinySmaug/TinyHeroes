#include "BackgroundElement.h"
#include <vector>
#include <string>


BackgroundElement::BackgroundElement(std::string file, sf::RenderWindow &window)
{
	layerTexture.loadFromFile(file);

	sf::Vector2u bgTextureSize = layerTexture.getSize();
	sf::Vector2f bgTextureScale(static_cast<float>(window.getSize().x) / bgTextureSize.x,
								static_cast<float>(window.getSize().y) / bgTextureSize.y);

	backgroundLayer.setTexture(layerTexture);
	backgroundLayer.scale(bgTextureScale);
}

BackgroundElement::~BackgroundElement()
{
}


void BackgroundElement::render(sf::RenderWindow & window)
{
	window.draw(backgroundLayer);
	backgroundLayer.move(-1280.0f, 0.0f);
	window.draw(backgroundLayer);
	backgroundLayer.move(2.0f*1280.0f, 0.0f);
	window.draw(backgroundLayer);
	backgroundLayer.move(-1280.0f, 0.0f);
}

void BackgroundElement::resize(sf::RenderWindow & window)
{
}

void BackgroundElement::update(float velocity, float deltaTime, sf::RenderWindow & window, sf::View & view)
{
	backgroundLayer.move(velocity * deltaTime, 0.0f);
	checkBounds(velocity, deltaTime, window, view);
}

void BackgroundElement::checkBounds(float velocity, float deltaTime, sf::RenderWindow & window, sf::View & view)
{
	float moveConst = 1280.0f - velocity*deltaTime;

	float viewCenterX = view.getCenter().x;
	float leftBound = viewCenterX - 640.0f;
	float rightBound = viewCenterX + 640.0f;

	if (backgroundLayer.getPosition().x > rightBound)
	{
		backgroundLayer.move(-1280.0f, 0.0f);
	}
	if (backgroundLayer.getPosition().x + 1280.0f < leftBound)
	{
		backgroundLayer.move(1280.0f, 0.0f);
	}
}
