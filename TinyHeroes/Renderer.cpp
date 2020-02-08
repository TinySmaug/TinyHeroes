#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() 
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 600), "Tiny Heroes", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
}

Renderer * Renderer::getInstance()
{
	if (!instance)
	{
		instance = new Renderer();
	}
	return instance;
}

sf::RenderWindow & Renderer::getWindow()
{
	return *window;
}

sf::View & Renderer::getView()
{
	return *view;
}

void Renderer::renderObjects()
{
	/* TODO: Unseen objects shouldn't be rendered
	float leftViewBound = view->getCenter().x - window->getSize().x / 2.0f;
	float rightViewBound = view->getCenter().x + window->getSize().x / 2.0f;
	float topViewBound = view->getCenter().y - window->getSize().y / 2.0f;
	float bottomViewBound = view->getCenter().y + window->getSize().y / 2.0f;
	*/

	for (auto object : renderableObjects)
	{
		object->render(*window);
	}	
}

void Renderer::resizeView()
{
	float aspectRatio = static_cast<float>(window->getSize().x) / static_cast<float>(window->getSize().y);
	view->setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}