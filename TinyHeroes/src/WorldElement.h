#pragma once
#include "Entity.h"
#include "Renderer.h"
#include "WorldInstance.h"

class WorldElement : public Entity
{
public:
	WorldElement(std::string texturePath, Renderer &renderer, WorldInstance& world, int depth);
	~WorldElement();

	void render(sf::RenderWindow & window) override;
	void onCollision(CollisionObject & other, sf::Vector2f& direction, sf::FloatRect& intersectionRect);
	void update(float deltaTime);

	void setPosition(sf::Vector2f position);
	
};