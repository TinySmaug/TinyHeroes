#pragma once
#include "RenderableObject.h"
#include "CollisionObject.h"
#include "Animation.h"
#include "WorldInstance.h"

static int ID = 0;

class Entity : public RenderableObject, public CollisionObject
{
public:
	Entity(std::string texturePath, int depth);
	virtual ~Entity();

	virtual void update(float deltaTime) = 0;
	void setTexture(std::string texturePath);
	sf::FloatRect getRenderableArea() { return m_body; };
	void destroy() const;
	void setScale(sf::Vector2f scale);
	void move(sf::Vector2f offset);
	void move(float offsetX, float offsetY);
	unsigned getID() { return m_id; }
	void setPosition(sf::Vector2f position);
	void setPosition(float posX, float posY);
	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
	sf::FloatRect getBody() const { return m_body; };

protected:
	unsigned m_id = ID++;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::FloatRect m_body;
	std::string m_filePath;
	Animation m_animation;

private:
	void setAnimations();
};

