#pragma once
#include "Entity.h"
#include "WorldInstance.h"

class Projectile : public Entity
{
public:
	Projectile(std::string texturePath, Renderer &renderer, WorldInstance& world, int depth, float speed, sf::Vector2f position, bool faceRight);
	~Projectile();

	void render(sf::RenderWindow &window);
	void update(float deltaTime);

private:
	float speed;
	bool faceRight;
};

