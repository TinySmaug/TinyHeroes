#include "BackgroundElement.h"
#include "Renderer.h"
#include <vector>
#include <string>


BackgroundElement::BackgroundElement(std::string file)
{
	layerTexture.loadFromFile(file);

	sf::Vector2u bgTextureSize = layerTexture.getSize();
	sf::Vector2f bgTextureScale(static_cast<float>(Renderer::getInstance().getView().getSize().x) / bgTextureSize.x,
		static_cast<float>(Renderer::getInstance().getView().getSize().y) / bgTextureSize.y);

	backgroundLayer.setTexture(layerTexture);
	backgroundLayer.scale(bgTextureScale);
}

BackgroundElement::~BackgroundElement()
{
}


void BackgroundElement::render()
{
	float leftViewBound = Renderer::getInstance().getView().getCenter().x - Renderer::getInstance().getView().getSize().x / 2.0f;
	float rightViewBound = Renderer::getInstance().getView().getCenter().x + Renderer::getInstance().getView().getSize().x / 2.0f;
	
	sf::FloatRect body;
	float viewSizeX = Renderer::getInstance().getView().getSize().x;
	//center layer
	Renderer::getInstance().getWindow().draw(backgroundLayer);
	//left layer
	backgroundLayer.move(-viewSizeX, 0.0f);
	body.left = backgroundLayer.getPosition().x;
	if (!(body.left + viewSizeX < leftViewBound))
	{
		Renderer::getInstance().getWindow().draw(backgroundLayer);
	}
	//right layer
	backgroundLayer.move(2.0f*viewSizeX, 0.0f);
	body.left = backgroundLayer.getPosition().x;
	if (!(body.left > rightViewBound))
	{
		Renderer::getInstance().getWindow().draw(backgroundLayer);
	}
	backgroundLayer.move(-viewSizeX, 0.0f);
}

void BackgroundElement::update(float velocity, float deltaTime)
{
	backgroundLayer.move(velocity * deltaTime, 0.0f);
	checkBounds(velocity, deltaTime);
}

void BackgroundElement::checkBounds(float velocity, float deltaTime)
{
	float moveConst = Renderer::getInstance().getView().getSize().x - velocity*deltaTime;

	float viewCenterX = Renderer::getInstance().getView().getCenter().x;
	float viewSizeX = Renderer::getInstance().getView().getSize().x;
	float leftBound = viewCenterX - Renderer::getInstance().getView().getSize().x / 2.0f;
	float rightBound = viewCenterX + Renderer::getInstance().getView().getSize().x / 2.0f;

	if (backgroundLayer.getPosition().x > rightBound)
	{
		backgroundLayer.move(-viewSizeX, 0.0f);
	}
	if (backgroundLayer.getPosition().x + viewSizeX < leftBound)
	{
		backgroundLayer.move(viewSizeX, 0.0f);
	}
}
