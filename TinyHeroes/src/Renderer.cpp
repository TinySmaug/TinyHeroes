#include "Renderer.h"
#include "RenderableObject.h"
#include <algorithm>

Renderer::Renderer() 
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 600), "Tiny Heroes", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 600.0f));
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

sf::RenderWindow & Renderer::getWindow() const
{
	return *window;
}

sf::View & Renderer::getView() const
{
	return *view;
}

void Renderer::addRenderableObject(RenderableObject * object)
{
	renderableObjects.emplace_back(object);
	std::stable_sort(renderableObjects.begin(), renderableObjects.end(),
		[](auto objA, auto objB) { return objA->getRenderDepth() < objB->getRenderDepth(); });
}

std::vector<RenderableObject*>::iterator Renderer::removeRenderableObject(std::vector<RenderableObject*>::iterator i)
{
	return renderableObjects.erase(i);
}

bool Renderer::outOfView(RenderableObject & object) const
{
	/* TODO: Unseen objects shouldn't be rendered
float leftViewBound = view->getCenter().x - view->getSize().x / 2.0f;
float rightViewBound = view->getCenter().x + view->getSize().x / 2.0f;
float topViewBound = view->getCenter().y - view->getSize().y / 2.0f;
float bottomViewBound = view->getCenter().y + view->getSize().y / 2.0f;
*/
	return false;
}

void Renderer::renderObjects()
{
	for (auto i = renderableObjects.begin(); i != renderableObjects.end();)
	{
		if ((*i) == nullptr)
		{
			i = removeRenderableObject(i);
		}
		else 
		{
			(*i)->render();
			++i;
		}
	}
}
