#include "CollisionObject.h"


CollisionObject::CollisionObject(sf::FloatRect& body)
	: m_body(body)
{
}

CollisionObject::~CollisionObject()
{
}

bool CollisionObject::checkCollision(CollisionObject & other)
{
	if (m_body.intersects(other.m_body, m_intersectionRect))
	{
		bool collisionOnYAxis = m_intersectionRect.width < m_intersectionRect.height;
		bool collisionOnLeft = other.m_body.left - m_body.left < 0.0f;
		bool collisionOnTop = other.m_body.top - m_body.top < 0.0f;

		float widthMultiplier = collisionOnYAxis ? collisionOnLeft ? 1.0f : -1.0f : 0.0f;
		float heightMultiplier = collisionOnYAxis ? 0 : collisionOnTop ? 1.0f : -1.0f;

		m_intersectionRect.width *= widthMultiplier;
		m_intersectionRect.height *= heightMultiplier;

		other.m_intersectionRect.width = m_intersectionRect.width * -1.0f;
		other.m_intersectionRect.height = m_intersectionRect.height * -1.0f;
		return true;
	}
	m_intersectionRect.width = 0.0f;
	m_intersectionRect.height = 0.0f;
	other.m_intersectionRect.width = 0.0f;
	other.m_intersectionRect.height = 0.0f;
	return false;
}