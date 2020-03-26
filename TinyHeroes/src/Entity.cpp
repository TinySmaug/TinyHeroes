#include "Entity.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include "CollisionEngine.h"

Entity::Entity(std::string texturePath, int depth)
	: CollisionObject(body), RenderableObject(depth)
{
	if (texturePath.length() != 0)
	{
		texture.loadFromFile(texturePath);
		texture.setRepeated(true);
		sprite.setTexture(texture);
		filePath = texturePath;
		setAnimations();
	}

	body.width = static_cast<float>(texture.getSize().x);
	body.height = static_cast<float>(texture.getSize().y);

	WorldInstance::getInstance().addAliveObject(this);
	Renderer::getInstance().addRenderableObject(this);
	CollisionEngine::getInstance().addCollisionObject(this);
}

Entity::~Entity()
{
}

void Entity::setTexture(std::string texturePath)
{
	if (texturePath.length() != 0)
	{
		texture.loadFromFile(texturePath);
		texture.setRepeated(true);
		sprite.setTexture(texture);
		body.width = static_cast<float>(texture.getSize().x);
		body.height = static_cast<float>(texture.getSize().y);
		filePath = texturePath;
		setAnimations();
	}
}

void Entity::setAnimations()
{
	std::string animationTxtPath = filePath;
	auto dotPosition = animationTxtPath.find_last_of('.');
	if (dotPosition != std::string::npos)
	{
		animationTxtPath.replace(animationTxtPath.begin() + dotPosition + 1, animationTxtPath.end(), "txt");
	}
	else
	{
		//wrong file path
	}
	animation.setAnimations(animationTxtPath);
	animation.setSprite(sprite);
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
	WorldInstance::getInstance().removeAliveObject(id);
	CollisionEngine::getInstance().removeCollisionObject(id);
}

void Entity::setScale(sf::Vector2f scale)
{
	sprite.setScale(scale);
	body.width *= scale.x;
	body.height *= scale.y;
}

void Entity::move(sf::Vector2f offset)
{
	sprite.move(offset);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;
}

void Entity::move(float offsetX, float offsetY)
{
	sprite.move(offsetX, offsetY);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;
}

void Entity::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;
}
void Entity::setPosition(float posX, float posY)
{
	sprite.setPosition(posX, posY);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;
}
