#include "Entity.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include "CollisionEngine.h"

Entity::Entity(std::string texturePath, int depth)
	: CollisionObject(body), RenderableObject(depth)
{
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);

	body.width = static_cast<float>(texture.getSize().x);
	body.height = static_cast<float>(texture.getSize().y);

	
	WorldInstance::getInstance().addAliveObject(this);
	Renderer::getInstance().addRenderableObject(this);
	CollisionEngine::getInstance().addCollisionObject(this);
}

Entity::~Entity()
{
}

void Entity::destroy() const
{
	auto posRO = std::find_if(Renderer::getInstance().getRenderableObjects().begin(), Renderer::getInstance().getRenderableObjects().end(),
		[this](RenderableObject* obj) {
		if (dynamic_cast<Entity*>(obj))
		{
			return this->id == (dynamic_cast<Entity*>(obj))->id;
		}
		else
		{
			return false;
		}});
	if (posRO != Renderer::getInstance().getRenderableObjects().end())
	{
		Renderer::getInstance().removeRenderableObject(posRO);
	}

	auto posAO = std::find_if(WorldInstance::getInstance().getAliveObjects().begin(), WorldInstance::getInstance().getAliveObjects().end(),
							[this](auto obj) { return this->id == obj->id; });
	if (posAO != WorldInstance::getInstance().getAliveObjects().end())
	{
		WorldInstance::getInstance().removeAliveObject(posAO);
	}

	auto posCO = std::find_if(CollisionEngine::getInstance().getCollisionObjects().begin(), 
		CollisionEngine::getInstance().getCollisionObjects().end(),
		[this](CollisionObject* obj) {
		if (dynamic_cast<Entity*>(obj))
		{
			return this->id == (dynamic_cast<Entity*>(obj))->id;
		}
		else
		{
			return false;
		}});
	if (posCO != CollisionEngine::getInstance().getCollisionObjects().end())
	{
		CollisionEngine::getInstance().removeCollisionObject(posCO);
	}
}

void Entity::setScale(sf::Vector2f scale)
{
	sprite.setScale(scale);
	body.width *= scale.x;
	body.height *= scale.y;
}

