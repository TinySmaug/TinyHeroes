#include "WorldElement.h"
#include "Renderer.h"

WorldElement::WorldElement(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	m_movable = true;
}

WorldElement::~WorldElement()
{
}

void WorldElement::render()
{
	Renderer::getInstance().getWindow().draw(m_sprite);
}

void WorldElement::onCollision(CollisionObject & other)
{
	if (m_intersectionRect.width < 0.0f)
	{
		//collision on the left
		move(m_intersectionRect.width, 0.0f);
	}
	else if (m_intersectionRect.width > 0.0f)
	{
		//collision on the right
		move(m_intersectionRect.width, 0.0f);
	}
	if (m_intersectionRect.height < 0.0f)
	{
		//collision on the bottom
		move(0.0f, m_intersectionRect.height);
		m_velocity.y = 0.0f;
	}
}

void WorldElement::onCollisionEnd(CollisionObject & other)
{
}

void WorldElement::update(float deltaTime)
{
	m_velocity.x = 0.0f;
	m_velocity.y += WorldInstance::getInstance().getGravity() * deltaTime;
	move(m_velocity * deltaTime);
}


