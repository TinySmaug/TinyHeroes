#include "Background.h"


Background::Background(std::string file, int layerNum, sf::RenderWindow &window)
{
	for (int i = 0; i < layerNum; i++)
	{
		std::string path = file;
		path.append("/").append(std::to_string(i)).append(".png");

		background.push_back(new BackgroundElement(path, window));
	}
}


Background::~Background()
{
}

void Background::render(sf::RenderWindow & window)
{
	for (auto layer : background)
	{
		layer->render(window);
	}
}

void Background::resize(sf::RenderWindow & window)
{

}

void Background::update(sf::Vector2f playerVelocity, float deltaTime, sf::RenderWindow & window, sf::View & view)
{
	float layerMultiplier = 0.9f;
	float velocity = playerVelocity.x / 2.5f;

	for (int i = background.size() - 1; i >= 0; i--)
	{
		background[i]->update(velocity, deltaTime, window, view);
		velocity *= layerMultiplier;
	}
}
