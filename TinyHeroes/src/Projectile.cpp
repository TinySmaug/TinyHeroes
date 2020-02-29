#include "Projectile.h"

Projectile::Projectile(std::string texturePath, Renderer &renderer, WorldInstance& world,
					   int depth, float speed, sf::Vector2f position, bool faceRight)
	: Entity(texturePath, renderer, world),speed(speed), faceRight(faceRight)
{
	this->depth = depth;
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(3.0f, 3.0f));
}


Projectile::~Projectile()
{
}

void Projectile::render(sf::RenderWindow & window)
{
	window.draw(sprite);
}

void Projectile::update(float deltaTime)
{
	if(faceRight)
		sprite.move(speed * deltaTime, 0.0f);
	else
		sprite.move(-speed * deltaTime, 0.0f);
}
