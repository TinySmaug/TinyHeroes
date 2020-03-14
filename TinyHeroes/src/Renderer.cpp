#include "Renderer.h"
#include "RenderableObject.h"
#include <algorithm>
#include "Background.h" //remove after fixing outOfView
#include "Entity.h"  //remove after fixing outOfView

Renderer::Renderer() 
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 600), "Tiny Heroes", sf::Style::Close | sf::Style::Resize);
	view = new sf::View(sf::Vector2f(window->getSize().x/2.0f, window->getSize().y / 2.0f), sf::Vector2f(window->getSize()));
	window->setView(getView());
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
	//Unseen objects shouldn't be rendered
	float leftViewBound = view->getCenter().x - view->getSize().x / 2.0f;
	float rightViewBound = view->getCenter().x + view->getSize().x / 2.0f;
	float topViewBound = view->getCenter().y - view->getSize().y / 2.0f;
	float bottomViewBound = view->getCenter().y + view->getSize().y / 2.0f;

	sf::FloatRect body = object.getRenderableArea();
	if (body.top > bottomViewBound || body.top + body.height < topViewBound ||
		body.left > rightViewBound || body.left + body.width < leftViewBound)
	{
		return true;
	}
	return false;
}

void Renderer::renderObjects()
{
	for (auto i = renderableObjects.begin(); i != renderableObjects.end(); ++i)
	{
		if (!outOfView(*(*i)) && !((*i)->isHidden()))
		{
			(*i)->render();
		}
	}
}
