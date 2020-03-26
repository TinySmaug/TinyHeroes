#pragma once
#include <vector>
#include <memory>

class CollisionObject;

class CollisionEngine
{
public:
	void checkCollisions();
	static CollisionEngine& getInstance();

	std::vector<CollisionObject*>& getCollisionObjects() { return collisionObjects; };
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
	std::vector<CollisionObject*> collisionObjects;
	std::vector<CollisionObject*> objectsToCollide;
	std::vector<unsigned> objectsToRemove;

	std::vector<std::pair<CollisionObject*, CollisionObject*>> collidedObjects;
};

