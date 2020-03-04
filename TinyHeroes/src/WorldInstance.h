#pragma once
#include <vector>

class Entity;
class Background;

class WorldInstance
{
public:
	static WorldInstance& getInstance();
	void updateObjects(float deltaTime);

	std::vector<Entity*>& getAliveObjects() { return aliveObjects; };
	void addAliveObject(Entity* object);
	void addAliveObject(Background* object);
	std::vector<Entity*>::iterator removeAliveObject(std::vector<Entity*>::iterator i);
	void setWorldSpeed(float speed) { worldSpeed = speed; };
	float getWorldSpeed() { return worldSpeed; };

private:
	WorldInstance();
	~WorldInstance();
	WorldInstance(WorldInstance const&) {};
	WorldInstance& operator=(WorldInstance const&) {};

private:
	std::vector<Entity*> aliveObjects;
	Background* background;
	float worldSpeed;
};

