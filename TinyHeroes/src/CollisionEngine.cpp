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

void CollisionEngine::addCollidedObjects(CollisionObject * first, CollisionObject * second)
{
	collidedObjects.emplace_back(std::make_pair(first, second));
}

void CollisionEngine::removeCollidedObjects(CollisionObject * first, CollisionObject * second)
{
	for (auto i = collidedObjects.begin(); i != collidedObjects.end(); i++)
	{
		if ((*i).first == first && (*i).second == second)
		{
			collidedObjects.erase(i);
			break;
		}
	}
}

bool CollisionEngine::areCollidedObjects(CollisionObject * first, CollisionObject * second)
{
	for (auto i = collidedObjects.begin(); i != collidedObjects.end(); i++)
	{
		if ((*i).first == first && (*i).second == second)
		{
			return true;
		}
	}
	return false;
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
				if (!areCollidedObjects((*i), (*j)))
				{
					addCollidedObjects((*i), (*j));
				}
				(*i)->onCollision(*(*j));
				(*j)->onCollision(*(*i));
			}
			else
			{
				if (areCollidedObjects((*i), (*j)))
				{
					removeCollidedObjects((*i), (*j));
					(*i)->onCollisionEnd(*(*j));
					(*j)->onCollisionEnd(*(*i));
				}
			}
		}
	}
}

