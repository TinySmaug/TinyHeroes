#pragma once
#include "Entity.h"

class WorldElement : public Entity
{
public:
	WorldElement(std::string texturePath, int depth);
	~WorldElement();

	void render() override;
	void onCollision(CollisionObject & other);
	void update(float deltaTime);

	void setPosition(sf::Vector2f position);
	
};