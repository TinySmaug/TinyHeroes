#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity

{
public:
	PlayerCharacter(std::string texturePath, int depth);
	~PlayerCharacter();

	void update(float deltaTime);
	void render() override;
	void onCollision(CollisionObject & other);

	sf::Vector2f getVelocity() const { return velocity; };
	sf::Vector2f getPosition() const { return sprite.getPosition(); }

private:
	sf::Vector2f velocity;
	float acceleration;
	float maxSpeed;

	bool attacking;
	bool canAttack;
	bool jumping;
	bool running;
	bool canJump;
	float jumpHeight;
};

