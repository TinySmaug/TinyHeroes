#include "Projectile.h"
#include "Renderer.h"
#include "PlayerCharacter.h"

Projectile::Projectile(std::string texturePath, int depth, float speed, sf::Vector2f position, bool faceRight)
	: Entity(texturePath, depth), faceRight(faceRight)
{
	//NOTE: so that the spawned projectile doesn't collide with the entity that spawned it
	faceRight ? sprite.setPosition(position) : sprite.setPosition(position.x - body.width, position.y);
	sprite.setScale(sf::Vector2f(3.0f, 3.0f));
	startingPosition = position;
	flyUpwards = true;
	this->speed = speed == 0.0f ? faceRight ? 500.0f : -500.0f : speed * 3.0f;
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
	if (flyUpwards)
	{
		velocity.y = -sqrtf(2.0f * 981.0f * 50.0f);
		flyUpwards = false;
	}
	velocity.y += WorldInstance::getInstance().getGravity() * deltaTime;
	velocity.x = speed;
	move(velocity * deltaTime);
}

void Projectile::onCollision(CollisionObject & other)
{
	destroy();
}
