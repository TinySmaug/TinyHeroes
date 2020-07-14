#include "Platform.h"
#include "Renderer.h"

Platform::Platform(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	m_movable = false;
}


Platform::~Platform()
{
}

void Platform::render()
{
	Renderer::getInstance().getWindow().draw(m_sprite);
}

void Platform::onCollision(CollisionObject & other)
{
}

void Platform::onCollisionEnd(CollisionObject & other)
{
}

void Platform::update(float deltaTime)
{
}

void Platform::setSize(int width, int height)
{
	sf::IntRect platformRect(0, 0, width, height);
	m_sprite.setTextureRect(platformRect);
	m_body.width = width;
	m_body.height = height;
}
