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
	m_objectsToCollide.emplace_back(object);
}

void CollisionEngine::removeCollisionObject(unsigned objectID)
{
	return m_objectsToRemove.emplace_back(objectID);
}

void CollisionEngine::updateCollisionObjectsVector()
{
	for (auto i : m_objectsToCollide)
	{
		m_collisionObjects.emplace_back(i);
	}
	for (auto i : m_objectsToRemove)
	{
		auto findResult = std::find_if(m_collisionObjects.begin(), m_collisionObjects.end(),
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

		if (findResult != m_collisionObjects.end())
		{
			m_collisionObjects.erase(findResult);
		}
	}
	m_objectsToCollide.clear();
	m_objectsToRemove.clear();
}

void CollisionEngine::addCollidedObjects(CollisionObject * first, CollisionObject * second)
{
	m_collidedObjects.emplace_back(std::make_pair(first, second));
}

void CollisionEngine::removeCollidedObjects(CollisionObject * first, CollisionObject * second)
{
	for (auto i = m_collidedObjects.begin(); i != m_collidedObjects.end(); i++)
	{
		if ((*i).first == first && (*i).second == second)
		{
			m_collidedObjects.erase(i);
			break;
		}
	}
}

bool CollisionEngine::areCollidedObjects(CollisionObject * first, CollisionObject * second)
{
	for (auto i = m_collidedObjects.begin(); i != m_collidedObjects.end(); i++)
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

	for (auto i = m_collisionObjects.begin(); i != m_collisionObjects.end(); ++i)
	{
		for (auto j = i + 1; j != m_collisionObjects.end(); ++j)
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

