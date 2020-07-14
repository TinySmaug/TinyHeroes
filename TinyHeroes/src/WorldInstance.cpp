#include "WorldInstance.h"
#include "Entity.h"
#include "Background.h"
#include "PlayerCharacter.h"

WorldInstance::WorldInstance()
{
	m_worldSpeed = 0.0f;
	m_gravity = 981.0f;
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

	for (auto i = m_aliveObjects.begin(); i != m_aliveObjects.end(); i++)
	{
		(*i)->update(deltaTime);
		if (dynamic_cast<PlayerCharacter*>(*i))
		{
			auto player = dynamic_cast<PlayerCharacter*>(*i);
			m_playerPosition = player->getPosition();
		}
	}
	if(m_background != nullptr)
		m_background->update(deltaTime);

}

void WorldInstance::updateAliveObjectsVector()
{
	for (auto i : m_objectsToSpawn)
	{
		m_aliveObjects.emplace_back(i);
	}
	for (auto i : m_objectsToRemove)
	{
		auto findResult = std::find_if(m_aliveObjects.begin(), m_aliveObjects.end(), [i](Entity* entity) { return entity->getID() == i; });

		if (findResult != m_aliveObjects.end())
		{
			m_aliveObjects.erase(findResult);
		}
	}
	m_objectsToSpawn.clear();
	m_objectsToRemove.clear();
}

void WorldInstance::addAliveObject(Entity * object)
{
	m_objectsToSpawn.emplace_back(object);
}

void WorldInstance::addAliveObject(Background * object)
{
	m_background = object;
}

void WorldInstance::removeAliveObject(unsigned entityID)
{
	return m_objectsToRemove.emplace_back(entityID);
}
