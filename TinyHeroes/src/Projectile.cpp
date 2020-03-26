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
	maxHeight = 50.0f;
	this->speed = speed == 0.0f ? faceRight ? 400.0f : -400.0f : speed * 2.0f;
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
		velocity.y = -sqrtf(2.0f * 981.0f * maxHeight);
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

void Projectile::onCollisionEnd(CollisionObject & other)
{
}
