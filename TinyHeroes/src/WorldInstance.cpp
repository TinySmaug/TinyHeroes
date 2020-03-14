#include "WorldInstance.h"
#include "Entity.h"
#include "Background.h"
#include "PlayerCharacter.h"

WorldInstance::WorldInstance()
{
	worldSpeed = 0.0f;
	gravity = 981.0f;
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
	updateAliveObjectsVector();

	for (auto i = aliveObjects.begin(); i != aliveObjects.end(); i++)
	{
		(*i)->update(deltaTime);
		if (dynamic_cast<PlayerCharacter*>(*i))
		{
			auto player = dynamic_cast<PlayerCharacter*>(*i);
			playerPosition = player->getPosition();
		}
	}
	if(background != nullptr)
		background->update(deltaTime);

}

void WorldInstance::updateAliveObjectsVector()
{
	for (auto i : objectsToSpawn)
	{
		aliveObjects.emplace_back(i);
	}
	for (auto i : objectsToRemove)
	{
		auto findResult = std::find_if(aliveObjects.begin(), aliveObjects.end(), [i](Entity* entity) { return entity->getID() == i; });

		if (findResult != aliveObjects.end())
		{
			aliveObjects.erase(findResult);
		}
	}
	objectsToSpawn.clear();
	objectsToRemove.clear();
}

void WorldInstance::addAliveObject(Entity * object)
{
	objectsToSpawn.emplace_back(object);
}

void WorldInstance::addAliveObject(Background * object)
{
	background = object;
}

void WorldInstance::removeAliveObject(unsigned entityID)
{
	return objectsToRemove.emplace_back(entityID);
}
