#pragma once
#include <vector>

class CollisionObject;

class CollisionEngine
{
public:
	void checkCollisions();
	static CollisionEngine& getInstance();

	std::vector<CollisionObject*>& getCollisionObjects() { return m_collisionObjects; };
	void addCollisionObject(CollisionObject* object);
	void removeCollisionObject(unsigned objectID);

private:
	CollisionEngine();
	~CollisionEngine();
	CollisionEngine(CollisionEngine const&) {};
	CollisionEngine& operator=(CollisionEngine const&) {};

	void updateCollisionObjectsVector();
	void addCollidedObjects(CollisionObject* first, CollisionObject* second);
	void removeCollidedObjects(CollisionObject* first, CollisionObject * second);
	bool areCollidedObjects(CollisionObject* first, CollisionObject* second);

private:
	std::vector<CollisionObject*> m_collisionObjects;
	std::vector<CollisionObject*> m_objectsToCollide;
	std::vector<unsigned> m_objectsToRemove;

	std::vector<std::pair<CollisionObject*, CollisionObject*>> m_collidedObjects;
};

