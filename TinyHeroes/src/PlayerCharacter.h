#pragma once
#include "Entity.h"
#include "Projectile.h"
#include "WorldInstance.h"

class PlayerCharacter : public Entity

{
public:
	PlayerCharacter(std::string texturePath, Renderer &renderer, WorldInstance& world, int depth);
	~PlayerCharacter();

	void update(float deltaTime);
	void render(sf::RenderWindow & window) override;
	void onCollision(CollisionObject & other, sf::Vector2f& direction, sf::FloatRect& intersectionRect);

	sf::Vector2f getVelocity() { return velocity; };
	sf::Vector2f getPosition() { return sprite.getPosition(); }

private:
	sf::Vector2f velocity;
	float acceleration;
	float maxSpeed;

	bool attacking;
	bool jumping;
	bool running;
	bool canJump;
	float jumpHeight;
};

