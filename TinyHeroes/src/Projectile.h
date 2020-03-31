#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(std::string texturePath, int depth, float kineticEnergy, sf::Vector2f position, bool faceRight);
	~Projectile();

	void render();
	void update(float deltaTime);
	void onCollision(CollisionObject & other);
	void onCollisionEnd(CollisionObject & other);

private:
	sf::Vector2f m_velocity;
	float m_speed;
	bool m_flyUpwards;
	float m_maxHeight;
};

