#pragma once
#include "Entity.h"

class WorldElement : public Entity
{
public:
	WorldElement(std::string texturePath, int depth);
	~WorldElement();

	void render() override;
	void onCollision(CollisionObject & other);
	void onCollisionEnd(CollisionObject & other);
	void update(float deltaTime);

private:
	sf::Vector2f velocity;
};