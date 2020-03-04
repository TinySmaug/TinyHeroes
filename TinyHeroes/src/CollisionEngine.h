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
	std::vector<CollisionObject*>::iterator removeCollisionObject(std::vector<CollisionObject*>::iterator i);

private:
	CollisionEngine();
	~CollisionEngine();
	CollisionEngine(CollisionEngine const&) {};
	CollisionEngine& operator=(CollisionEngine const&) {};

private:
	std::vector<CollisionObject*> collisionObjects;
};

