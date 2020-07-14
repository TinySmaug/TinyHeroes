#include "Renderer.h"
#include "RenderableObject.h"
#include <algorithm>
#include "Background.h" //remove after fixing outOfView
#include "Entity.h"  //remove after fixing outOfView

Renderer::Renderer() 
{
	m_window = new sf::RenderWindow(sf::VideoMode(1280, 600), "Tiny Heroes", sf::Style::Close | sf::Style::Resize);
	m_view = new sf::View(sf::Vector2f(m_window->getSize().x/2.0f, m_window->getSize().y / 2.0f), sf::Vector2f(m_window->getSize()));
	m_view->setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	m_window->setView(getView());
}

Renderer::~Renderer()
{
	delete m_window;
	delete m_view;
}

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

sf::RenderWindow & Renderer::getWindow() const
{
	return *m_window;
}

sf::View & Renderer::getView() const
{
	return *m_view;
}

void Renderer::addRenderableObject(RenderableObject * object)
{
	m_renderableObjects.emplace_back(object);
	std::stable_sort(m_renderableObjects.begin(), m_renderableObjects.end(),
		[](auto objA, auto objB) { return objA->getRenderDepth() < objB->getRenderDepth(); });
}

std::vector<RenderableObject*>::iterator Renderer::removeRenderableObject(std::vector<RenderableObject*>::iterator i)
{
	return m_renderableObjects.erase(i);
}

bool Renderer::outOfView(RenderableObject & object) const
{
	//Unseen objects shouldn't be rendered
	float leftViewBound = m_view->getCenter().x - m_view->getSize().x / 2.0f;
	float rightViewBound = m_view->getCenter().x + m_view->getSize().x / 2.0f;
	float topViewBound = m_view->getCenter().y - m_view->getSize().y / 2.0f;
	float bottomViewBound = m_view->getCenter().y + m_view->getSize().y / 2.0f;

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
	for (auto i = m_renderableObjects.begin(); i != m_renderableObjects.end(); ++i)
	{
		if (!outOfView(*(*i)) && !((*i)->isHidden()))
		{
			(*i)->render();
		}
	}
}
