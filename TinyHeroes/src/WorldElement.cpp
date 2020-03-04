#include "WorldElement.h"
#include "Renderer.h"

WorldElement::WorldElement(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
}

WorldElement::~WorldElement()
{
}

void WorldElement::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void WorldElement::onCollision(CollisionObject & other)
{
}

void WorldElement::update(float deltaTime)
{
}

void WorldElement::setPosition(sf::Vector2f position)
{
	sprite.move(position);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;
}


