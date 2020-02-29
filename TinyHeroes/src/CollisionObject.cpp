#include "CollisionObject.h"

CollisionObject::CollisionObject(sf::FloatRect& body)
	: body(body)
{
}

CollisionObject::~CollisionObject()
{
}

bool CollisionObject::checkCollision(CollisionObject & other, sf::Vector2f& direction, sf::FloatRect& intersectionRect) const
{
	
	if(body.intersects(other.body, intersectionRect))
	{
		if (intersectionRect.width < intersectionRect.height)
		{
			if (other.body.left - body.left > 0.0f)
			{
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else
		{
			if (other.body.top - body.top > 0.0f)
			{
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}