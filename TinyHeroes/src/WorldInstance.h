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

	std::vector<Entity*>& getAliveObjects() { return m_aliveObjects; };
	void addAliveObject(Entity* object);
    void addAliveObject(Background* object);
	void removeAliveObject(unsigned entityID);
	void setWorldSpeed(float speed) { m_worldSpeed = speed; };
	float getWorldSpeed() { return m_worldSpeed; };
	float getGravity() { return m_gravity; };
	sf::Vector2f getPlayerPosition() { return m_playerPosition; };

private:
	WorldInstance();
	~WorldInstance();
	WorldInstance(WorldInstance const&) {};
	WorldInstance& operator=(WorldInstance const&) {};

	void updateAliveObjectsVector();

private:
    std::vector<Entity*> m_aliveObjects;
    std::vector<Entity*> m_objectsToSpawn;
    std::vector<unsigned> m_objectsToRemove;
	Background* m_background;
	float m_worldSpeed;
	float m_gravity;
	sf::Vector2f m_playerPosition;
};

