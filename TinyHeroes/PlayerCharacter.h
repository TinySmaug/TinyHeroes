#pragma once
#include "Entity.h"
#include "Animation.h"

class PlayerCharacter : public Entity

{
public:
	PlayerCharacter(std::string texturePath);
	~PlayerCharacter();

	void update(float deltaTime);

	void setX(float x) { sprite.setPosition(x, sprite.getPosition().y);  };
	sf::Vector2f getVelocity() { return velocity; };

	sf::Vector2f getPosition() { return sprite.getPosition(); }

private:
	Animation animation;

	sf::Vector2f velocity;
	float acceleration;
	float maxSpeed;

	bool jumping;
	bool running;
	bool canJump;
	float jumpHeight;
};

