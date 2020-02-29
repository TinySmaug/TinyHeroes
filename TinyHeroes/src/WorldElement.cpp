#include "WorldElement.h"

WorldElement::WorldElement(std::string texturePath, Renderer &renderer, WorldInstance& world, int depth)
	: Entity(texturePath, renderer, world)
{
	this->depth = depth;
}

WorldElement::~WorldElement()
{
}

void WorldElement::render(sf::RenderWindow & window)
{
	window.draw(sprite);
}

void WorldElement::onCollision(CollisionObject & other, sf::Vector2f& direction, sf::FloatRect& intersectionRect)
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


