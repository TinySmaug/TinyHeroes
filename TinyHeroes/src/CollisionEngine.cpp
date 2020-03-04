#include "CollisionEngine.h"
#include "CollisionObject.h"

CollisionEngine::CollisionEngine()
{
}


CollisionEngine::~CollisionEngine()
{
}

CollisionEngine & CollisionEngine::getInstance()
{
	static CollisionEngine instance;
	return instance;
}

void CollisionEngine::addCollisionObject(CollisionObject * object)
{
	collisionObjects.emplace_back(object);
}

std::vector<CollisionObject*>::iterator CollisionEngine::removeCollisionObject(std::vector<CollisionObject*>::iterator i)
{
	return collisionObjects.erase(i);
}

void CollisionEngine::checkCollisions()
{
	for (auto i = collisionObjects.begin(); i != collisionObjects.end();)
	{
		if ((*i) == nullptr)
		{
			i = removeCollisionObject(i);
			continue;
		}
		for (auto j = i + 1; j != collisionObjects.end();)
		{
			
			if ((*j) == nullptr)
			{
				j = removeCollisionObject(j);
				continue;
			}
			if ((*i)->checkCollision(*(*j)))
			{
				(*i)->onCollision(*(*j));
				(*j)->onCollision(*(*i));
			}
			++j;
		}
		++i;
	}
}

