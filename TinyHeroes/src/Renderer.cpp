#include "Renderer.h"
#include <algorithm>

Renderer::Renderer() 
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 600), "Tiny Heroes", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
}

Renderer::~Renderer()
{
	delete window;
	delete view;
}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
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

	std::stable_sort(renderableObjects.begin(), renderableObjects.end(),
		[](auto objA, auto objB) { return objA->getDepth() < objB->getDepth(); });

	for (auto object : renderableObjects)
	{
		object->render(*window);
	}	
}
