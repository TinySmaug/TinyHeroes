#pragma once
#include <vector>

class Entity;

class WorldInstance
{
public:
	WorldInstance();
	~WorldInstance();

	void updateObjects(float deltaTime);

public:
	std::vector< Entity* > aliveObjects;
};

