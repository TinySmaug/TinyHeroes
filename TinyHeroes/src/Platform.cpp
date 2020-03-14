#include "Platform.h"
#include "Renderer.h"

Platform::Platform(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	movable = false;
}


Platform::~Platform()
{
}

void Platform::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void Platform::onCollision(CollisionObject & other)
{
}

void Platform::update(float deltaTime)
{
}

void Platform::setSize(int width, int height)
{
	sf::IntRect platformRect(0, 0, width, height);
	sprite.setTextureRect(platformRect);
	body.width = width;
	body.height = height;
}
