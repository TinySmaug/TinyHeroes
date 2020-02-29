#pragma once
#include "RenderableObject.h"
#include "CollisionObject.h"
#include "Animation.h"
#include "Renderer.h"
#include "WorldInstance.h"

class Entity : public RenderableObject, public CollisionObject
{
public:
	Entity(std::string texturePath, Renderer &renderer, WorldInstance& world);
	virtual ~Entity();

	virtual void update(float deltaTime) = 0;

protected:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::FloatRect body;
	Animation animation;
	Renderer& renderer;
	WorldInstance& world;
};

