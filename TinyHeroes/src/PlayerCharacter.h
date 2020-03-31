#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity

{
public:
	PlayerCharacter(std::string texturePath, int depth);
	~PlayerCharacter();

	void update(float deltaTime) override;
	void render() override;
	void onCollision(CollisionObject & other) override;
	void onCollisionEnd(CollisionObject & other) override;

	void addInputHandlerFunctions();
	void removeInputHandlerFunctions();

	sf::Vector2f getVelocity() const { return velocity; };

private:
	void setCurrentAnimationInfo();
	void throwRock();

	void handleLeftMouseButtonClick(float deltaTime);
	void handleRightMouseButtonClick(float deltaTime);
	void handleAKeyboardButtonPressed(float deltaTime);
	void handleDKeyboardButtonPressed(float deltaTime);
	void handleSpaceKeyboardButtonPressed(float deltaTime);
	void handleLShiftKeyboardButtonPressed(float deltaTime);

	void handleLeftMouseButtonReleased(float deltaTime);
	void handleRightMouseButtonReleased(float deltaTime);
	void handleAKeyboardButtonReleased(float deltaTime);
	void handleDKeyboardButtonReleased(float deltaTime);
	void handleSpaceKeyboardButtonReleased(float deltaTime);
	void handleLShiftKeyboardButtonReleased(float deltaTime);

private:
	typedef struct state {
		bool walkAttack;
		bool attacking;
		bool throwing;
		bool jumping;
		bool running;
		bool pushing;
		bool walking;
		bool hurt;
	} state;
	state playerState;
	sf::Vector2f velocity;
	float speedMultiplier;
	float acceleration;
	float maxSpeed;
	bool canThrow;
	bool canJump;
	bool canAttack;
	bool canWalkAttack;
	float jumpHeight;
	bool movingLeft;
	bool movingRight;
};

