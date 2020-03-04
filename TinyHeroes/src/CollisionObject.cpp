#include "CollisionObject.h"

CollisionObject::CollisionObject(sf::FloatRect& body)
	: body(body)
{
}

CollisionObject::~CollisionObject()
{
}

bool CollisionObject::checkCollision(CollisionObject & other)
{
	if (body.intersects(other.body, intersectionRect))
	{
		bool collisionOnYAxis = intersectionRect.width < intersectionRect.height;
		bool collisionOnLeft = other.body.left - body.left < 0.0f;
		bool collisionOnTop = other.body.top - body.top < 0.0f;

		float widthMultiplier = collisionOnYAxis ? collisionOnLeft ? 1.0f : -1.0f : 0.0f;
		float heightMultiplier = collisionOnYAxis ? 0 : collisionOnTop ? 1.0f : -1.0f;

		intersectionRect.width *= widthMultiplier;
		intersectionRect.height *= heightMultiplier;

		other.intersectionRect.width = intersectionRect.width * -1.0f;
		other.intersectionRect.height = intersectionRect.height * -1.0f;
		return true;
	}
	return false;
}