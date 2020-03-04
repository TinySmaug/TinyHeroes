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
	void destroy() const;
	void setScale(sf::Vector2f scale);

protected:
	int id = ID++;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::FloatRect body;
	Animation animation;
};

