#include "Projectile.h"
#include "Renderer.h"

Projectile::Projectile(std::string texturePath, int depth, float speed, sf::Vector2f position, bool faceRight)
	: Entity(texturePath, depth),speed(speed), faceRight(faceRight)
{
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(3.0f, 3.0f));
}


Projectile::~Projectile()
{
}

void Projectile::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void Projectile::update(float deltaTime)
{
	if(faceRight)
		sprite.move(speed * deltaTime, 0.0f);
	else
		sprite.move(-speed * deltaTime, 0.0f);
}

void Projectile::onCollision(CollisionObject & other)
{
}
