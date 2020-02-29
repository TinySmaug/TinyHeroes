#include "WorldInstance.h"
#include "Entity.h"

WorldInstance::WorldInstance()
{
}


WorldInstance::~WorldInstance()
{
}

void WorldInstance::updateObjects(float deltaTime)
{
	for (auto object : aliveObjects)
	{
		object->update(deltaTime);
	}
}
