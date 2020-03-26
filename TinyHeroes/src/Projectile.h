#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(std::string texturePath, int depth, float speed, sf::Vector2f position, bool faceRight);
	~Projectile();

	void render();
	void update(float deltaTime);
	void onCollision(CollisionObject & other);
	void onCollisionEnd(CollisionObject & other);

private:
	sf::Vector2f velocity;
	sf::Vector2f startingPosition;
	float speed;
	bool flyUpwards;
	float maxHeight;
	bool faceRight;
};

