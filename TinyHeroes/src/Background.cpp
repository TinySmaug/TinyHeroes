#include "Background.h"
#include "Renderer.h"
#include "WorldInstance.h"

Background::Background(std::string file, int layerNum, int renderDepth)
	: RenderableObject(renderDepth)
{
	for (int i = 0; i < layerNum; i++)
	{
		std::string path = file;
		path.append("/").append(std::to_string(i)).append(".png");

		background.push_back(new BackgroundElement(path));
	}

	Renderer::getInstance().addRenderableObject(this);
	WorldInstance::getInstance().addAliveObject(this);
}


Background::~Background()
{
	for (auto i : background)
		delete i;
}

void Background::render()
{
	for (auto layer : background)
	{
		layer->render();
	}
}

sf::FloatRect Background::getRenderableArea()
{
	sf::FloatRect body; 
	body.width = Renderer::getInstance().getView().getSize().x * 3.0f;
	body.height = Renderer::getInstance().getView().getSize().y;
	body.left = Renderer::getInstance().getView().getCenter().x - Renderer::getInstance().getView().getSize().x / 2.0f;
	body.top = Renderer::getInstance().getView().getCenter().y - Renderer::getInstance().getView().getSize().y / 2.0f;

	return body;
}

/*
void Background::setTexture(std::string file, int layerNum)
{
	for (int i = 0; i < layerNum; i++)
	{
		std::string path = file;
		path.append("/").append(std::to_string(i)).append(".png");

		background.push_back(new BackgroundElement(path));
	}
}
*/

void Background::update(float deltaTime)
{
	float layerMultiplier = 0.5f;
	float velocity = WorldInstance::getInstance().getWorldSpeed() / 2.5f;

	for (int i = background.size() - 1; i >= 0; i--)
	{
		background[i]->update(velocity, deltaTime);
		velocity *= layerMultiplier;
	}
}
