#include "BackgroundElement.h"
#include "Renderer.h"
#include <vector>
#include <string>


BackgroundElement::BackgroundElement(std::string file)
{
	m_layerTexture.loadFromFile(file);

	sf::Vector2u bgTextureSize = m_layerTexture.getSize();
	sf::Vector2f bgTextureScale(static_cast<float>(Renderer::getInstance().getView().getSize().x) / bgTextureSize.x,
		static_cast<float>(Renderer::getInstance().getView().getSize().y) / bgTextureSize.y);

	m_backgroundLayer.setTexture(m_layerTexture);
	m_backgroundLayer.scale(bgTextureScale);
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
	Renderer::getInstance().getWindow().draw(m_backgroundLayer);
	//left layer
	m_backgroundLayer.move(-viewSizeX, 0.0f);
	body.left = m_backgroundLayer.getPosition().x;
	if (!(body.left + viewSizeX < leftViewBound))
	{
		Renderer::getInstance().getWindow().draw(m_backgroundLayer);
	}
	//right layer
	m_backgroundLayer.move(2.0f*viewSizeX, 0.0f);
	body.left = m_backgroundLayer.getPosition().x;
	if (!(body.left > rightViewBound))
	{
		Renderer::getInstance().getWindow().draw(m_backgroundLayer);
	}
	m_backgroundLayer.move(-viewSizeX, 0.0f);
}

void BackgroundElement::update(float velocity, float deltaTime)
{
	m_backgroundLayer.move(velocity * deltaTime, 0.0f);
	checkBounds(velocity, deltaTime);
}

void BackgroundElement::checkBounds(float velocity, float deltaTime)
{
	float moveConst = Renderer::getInstance().getView().getSize().x - velocity*deltaTime;

	float viewCenterX = Renderer::getInstance().getView().getCenter().x;
	float viewSizeX = Renderer::getInstance().getView().getSize().x;
	float leftBound = viewCenterX - Renderer::getInstance().getView().getSize().x / 2.0f;
	float rightBound = viewCenterX + Renderer::getInstance().getView().getSize().x / 2.0f;

	if (m_backgroundLayer.getPosition().x > rightBound)
	{
		m_backgroundLayer.move(-viewSizeX, 0.0f);
	}
	if (m_backgroundLayer.getPosition().x + viewSizeX < leftBound)
	{
		m_backgroundLayer.move(viewSizeX, 0.0f);
	}
}
