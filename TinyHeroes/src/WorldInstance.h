#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

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
	void removeAliveObject(unsigned entityID);
	void setWorldSpeed(float speed) { worldSpeed = speed; };
	float getWorldSpeed() { return worldSpeed; };
	float getGravity() { return gravity; };
	sf::Vector2f getPlayerPosition() { return playerPosition; };

private:
	WorldInstance();
	~WorldInstance();
	WorldInstance(WorldInstance const&) {};
	WorldInstance& operator=(WorldInstance const&) {};

	void updateAliveObjectsVector();

private:
    std::vector<Entity*> aliveObjects;
    std::vector<Entity*> objectsToSpawn;
    std::vector<unsigned> objectsToRemove;
	Background* background;
	float worldSpeed;
	float gravity;
	sf::Vector2f playerPosition;
};

