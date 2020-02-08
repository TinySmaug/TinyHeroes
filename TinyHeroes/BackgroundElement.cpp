#include "BackgroundElement.h"
#include <vector>
#include <string>


BackgroundElement::BackgroundElement(std::string file, sf::RenderWindow &window)
{
	for (int i = 0; i < 7; i++)
	{
		std::string path = file;
		path.append("/").append(std::to_string(i)).append(".png");

		sf::Texture layer;
		layer.loadFromFile(path);
		bgTextureLayers.push_back(new sf::Texture(layer));

		sf::Vector2u bgTextureSize = layer.getSize();
		sf::Vector2f bgTextureScale(static_cast<float>(window.getSize().x) / bgTextureSize.x,
									static_cast<float>(window.getSize().y) / bgTextureSize.y);

		sf::Sprite background;

		background.setTexture(*bgTextureLayers[i]);
		background.scale(bgTextureScale);
		backgrounds.push_back(background);
	}
}

BackgroundElement::~BackgroundElement()
{
}

void BackgroundElement::render(sf::RenderWindow & window)
{
	for (auto background : backgrounds) 
	{
		window.draw(background);
	}
}

void BackgroundElement::update(sf::Vector2f playerVelocity, float deltaTime, sf::RenderWindow & window, sf::View & view)
{
	float layerMultiplier = 0.9f;
	float runningMultiplier = 1.3f;
	float jumpingMultiplier = 1.5f;
	float velocity = playerVelocity.x / 2.5f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		deltaTime *= runningMultiplier;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		deltaTime *= jumpingMultiplier;
	}
	
	for (int i = backgrounds.size() - 1; i>=0; i--)
	{
		backgrounds[i].move(velocity * deltaTime, 0.0f);
		velocity *= layerMultiplier;
	}

	checkBounds(velocity, deltaTime, window, view);
}

void BackgroundElement::checkBounds(float velocity, float deltaTime, sf::RenderWindow & window, sf::View & view)
{
	float moveConst = 1280.0f - velocity*deltaTime;

	float viewCenterX = view.getCenter().x;
	float leftBound = viewCenterX - 640.0f;
	float rightBound = viewCenterX + 640.0f;
	
	for(int i = 0; i < backgrounds.size(); i++)
	{
		if (backgrounds[i].getPosition().x > rightBound)
		{
			backgrounds[i].move(-1280.0f, 0.0f);
		}
		if (backgrounds[i].getPosition().x < leftBound)
		{
			backgrounds[i].move(1280.0f, 0.0f);
		}
		backgrounds[i].move(-moveConst, 0.0f);
		window.draw(backgrounds[i]);
		backgrounds[i].move(2.0f*moveConst, 0.0f);
		window.draw(backgrounds[i]);
		backgrounds[i].move(-moveConst, 0.0f);		
	}
}
