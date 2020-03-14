#pragma once
#include <vector>

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

private:
	std::vector<CollisionObject*> collisionObjects;
	std::vector<CollisionObject*> objectsToCollide;
	std::vector<unsigned> objectsToRemove;
};

