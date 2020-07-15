#include "Projectile.h"
#include "Renderer.h"
#include "Enemy.h"

Projectile::Projectile(std::string texturePath, int depth, float kineticEnergy, sf::Vector2f position, bool faceRight)
	: Entity(texturePath, depth)
{
	//NOTE: so that the spawned projectile doesn't collide with the entity that spawned it
	faceRight ? m_sprite.setPosition(position) : m_sprite.setPosition(position.x - m_body.width, position.y);
	m_sprite.setScale(sf::Vector2f(3.0f, 3.0f));
	m_flyUpwards = true;
	m_maxHeight = 50.0f;
	m_speed = 400.0f;
	
	m_speed += abs(kineticEnergy) / 2.5f;
	m_speed *= faceRight ? 1.0f : -1.0f;
}

Projectile::~Projectile()
{
}

void Projectile::render()
{
	Renderer::getInstance().getWindow().draw(m_sprite);
}

void Projectile::update(float deltaTime)
{
	if (m_flyUpwards)
	{
		m_velocity.y = -sqrtf(2.0f * 981.0f * m_maxHeight);
		m_flyUpwards = false;
	}
	m_velocity.y += WorldInstance::getInstance().getGravity() * deltaTime;
	m_velocity.x = m_speed;
	move(m_velocity * deltaTime);
}

void Projectile::onCollision(CollisionObject & other)
{
	if (!dynamic_cast<Enemy*>(&other) || !dynamic_cast<Enemy*>(&other)->isDead())
	{
		destroy();
	}
}

void Projectile::onCollisionEnd(CollisionObject & other)
{
}
