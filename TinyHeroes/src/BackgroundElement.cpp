#include "BackgroundElement.h"
#include "Renderer.h"
#include <vector>
#include <string>


BackgroundElement::BackgroundElement(std::string file)
{
	layerTexture.loadFromFile(file);

	sf::Vector2u bgTextureSize = layerTexture.getSize();
	sf::Vector2f bgTextureScale(static_cast<float>(Renderer::getInstance().getWindow().getSize().x) / bgTextureSize.x,
								static_cast<float>(Renderer::getInstance().getWindow().getSize().y) / bgTextureSize.y);

	backgroundLayer.setTexture(layerTexture);
	backgroundLayer.scale(bgTextureScale);
}

BackgroundElement::~BackgroundElement()
{
}


void BackgroundElement::render()
{
	Renderer::getInstance().getWindow().draw(backgroundLayer);
	backgroundLayer.move(-1280.0f, 0.0f);
	Renderer::getInstance().getWindow().draw(backgroundLayer);
	backgroundLayer.move(2.0f*1280.0f, 0.0f);
	Renderer::getInstance().getWindow().draw(backgroundLayer);
	backgroundLayer.move(-1280.0f, 0.0f);
}

void BackgroundElement::update(float velocity, float deltaTime)
{
	backgroundLayer.move(velocity * deltaTime, 0.0f);
	checkBounds(velocity, deltaTime);
}

void BackgroundElement::checkBounds(float velocity, float deltaTime)
{
	float moveConst = 1280.0f - velocity*deltaTime;

	float viewCenterX = Renderer::getInstance().getView().getCenter().x;
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
