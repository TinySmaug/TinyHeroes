#include "WorldInstance.h"
#include "Entity.h"
#include "Background.h"

WorldInstance::WorldInstance()
{
}

WorldInstance::~WorldInstance()
{
	
}

WorldInstance& WorldInstance::getInstance()
{
	static WorldInstance instance;
	return instance;
}

void WorldInstance::updateObjects(float deltaTime)
{
	for (auto i = aliveObjects.begin(); i!=aliveObjects.end();)
	{
		if ((*i) == nullptr)
		{
			i = removeAliveObject(i);
		}
		else
		{
			(*i)->update(deltaTime);
			++i;
		}
	}
	if(background != nullptr)
		background->update(deltaTime);
}

void WorldInstance::addAliveObject(Entity * object)
{
	aliveObjects.emplace_back(object);
}

void WorldInstance::addAliveObject(Background * object)
{
	background = object;
}

std::vector<Entity*>::iterator WorldInstance::removeAliveObject(std::vector<Entity*>::iterator i)
{
	return aliveObjects.erase(i);
}
