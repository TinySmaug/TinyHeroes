#include "Background.h"


Background::Background(std::string file, int layerNum, Renderer &renderer, int depth)
{
	for (int i = 0; i < layerNum; i++)
	{
		std::string path = file;
		path.append("/").append(std::to_string(i)).append(".png");

		background.push_back(new BackgroundElement(path, renderer.getWindow()));
	}
	this->depth = depth;
	renderer.renderableObjects.push_back(this);
}


Background::~Background()
{
	for (auto i : background)
		delete i;
}

void Background::render(sf::RenderWindow & window)
{
	for (auto layer : background)
	{
		layer->render(window);
	}
}

void Background::update(sf::Vector2f playerVelocity, float deltaTime, Renderer &renderer)
{
	float layerMultiplier = 0.5f;
	float velocity = playerVelocity.x / 2.5f;

	for (int i = background.size() - 1; i >= 0; i--)
	{
		background[i]->update(velocity, deltaTime, renderer.getWindow(), renderer.getView());
		velocity *= layerMultiplier;
	}
}
