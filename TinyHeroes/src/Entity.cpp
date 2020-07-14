#include "Entity.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include "CollisionEngine.h"

Entity::Entity(std::string texturePath, int depth)
	: CollisionObject(m_body), RenderableObject(depth)
{
	if (texturePath.length() != 0)
	{
		m_texture.loadFromFile(texturePath);
		m_texture.setRepeated(true);
		m_sprite.setTexture(m_texture);
		m_filePath = texturePath;
		setAnimations();
	}

	m_body.width = static_cast<float>(m_texture.getSize().x);
	m_body.height = static_cast<float>(m_texture.getSize().y);

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
		m_texture.loadFromFile(texturePath);
		m_texture.setRepeated(true);
		m_sprite.setTexture(m_texture);
		m_body.width = static_cast<float>(m_texture.getSize().x);
		m_body.height = static_cast<float>(m_texture.getSize().y);
		m_filePath = texturePath;
		setAnimations();
	}
}

void Entity::setAnimations()
{
	std::string animationTxtPath = m_filePath;
	auto dotPosition = animationTxtPath.find_last_of('.');
	if (dotPosition != std::string::npos)
	{
		animationTxtPath.replace(animationTxtPath.begin() + dotPosition + 1, animationTxtPath.end(), "txt");
	}
	else
	{
		//wrong file path
	}
	m_animation.setAnimations(animationTxtPath);
	m_animation.setSprite(m_sprite);
}



void Entity::destroy() const
{
	auto posRO = std::find_if(Renderer::getInstance().getRenderableObjects().begin(), Renderer::getInstance().getRenderableObjects().end(),
		[this](RenderableObject* obj) {
		if (dynamic_cast<Entity*>(obj))
		{
			return this->m_id == (dynamic_cast<Entity*>(obj))->m_id;
		}
		else
		{
			return false;
		}});
	if (posRO != Renderer::getInstance().getRenderableObjects().end())
	{
		Renderer::getInstance().removeRenderableObject(posRO);
	}
	WorldInstance::getInstance().removeAliveObject(m_id);
	CollisionEngine::getInstance().removeCollisionObject(m_id);
}

void Entity::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	m_body.width *= scale.x;
	m_body.height *= scale.y;
}

void Entity::move(sf::Vector2f offset)
{
	m_sprite.move(offset);
	m_body.left = m_sprite.getPosition().x;
	m_body.top = m_sprite.getPosition().y;
}

void Entity::move(float offsetX, float offsetY)
{
	m_sprite.move(offsetX, offsetY);
	m_body.left = m_sprite.getPosition().x;
	m_body.top = m_sprite.getPosition().y;
}

void Entity::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
	m_body.left = m_sprite.getPosition().x;
	m_body.top = m_sprite.getPosition().y;
}
void Entity::setPosition(float posX, float posY)
{
	m_sprite.setPosition(posX, posY);
	m_body.left = m_sprite.getPosition().x;
	m_body.top = m_sprite.getPosition().y;
}
