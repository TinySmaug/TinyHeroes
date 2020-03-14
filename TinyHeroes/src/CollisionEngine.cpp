#include "CollisionEngine.h"
#include "CollisionObject.h"
#include "Entity.h"

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
	objectsToCollide.emplace_back(object);
}

void CollisionEngine::removeCollisionObject(unsigned objectID)
{
	return objectsToRemove.emplace_back(objectID);
}

void CollisionEngine::updateCollisionObjectsVector()
{
	for (auto i : objectsToCollide)
	{
		collisionObjects.emplace_back(i);
	}
	for (auto i : objectsToRemove)
	{
		auto findResult = std::find_if(collisionObjects.begin(), collisionObjects.end(),
			[i](auto obj) {
			if (dynamic_cast<Entity*>(obj))
			{
				return (dynamic_cast<Entity*>(obj))->getID() == i;
			}
			else
			{
				return false;
			}
		});

		if (findResult != collisionObjects.end())
		{
			collisionObjects.erase(findResult);
		}
	}
	objectsToCollide.clear();
	objectsToRemove.clear();
}

void CollisionEngine::checkCollisions()
{
	updateCollisionObjectsVector();

	for (auto i = collisionObjects.begin(); i != collisionObjects.end(); ++i)
	{
		for (auto j = i + 1; j != collisionObjects.end(); ++j)
		{
			if ((*i)->checkCollision(*(*j)))
			{
				(*i)->onCollision(*(*j));
				(*j)->onCollision(*(*i));
			}
		}
	}
}

