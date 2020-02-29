#include "Entity.h"

Entity::Entity(std::string texturePath, Renderer &renderer, WorldInstance& world)
	: CollisionObject(body), renderer(renderer), world(world)
{
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);

	body.width = static_cast<float>(texture.getSize().x);
	body.height = static_cast<float>(texture.getSize().y);

	renderer.renderableObjects.push_back(this);
	world.aliveObjects.push_back(this);
}

Entity::~Entity()
{
}

