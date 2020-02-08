#pragma once
#include "RenderableObject.h"
#include "CollisionObject.h"

class Entity : public RenderableObject, public CollisionObject
{
public:
	Entity(std::string texturePath);
	~Entity();

	void render(sf::RenderWindow &window);

protected:
	sf::Sprite sprite;
	sf::Texture texture;
};

