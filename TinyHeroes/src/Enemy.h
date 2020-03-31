#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(std::string texturePath, int depth);
	~Enemy();

	void update(float deltaTime) override;
	void render() override;
	void onCollision(CollisionObject & other) override;
	void onCollisionEnd(CollisionObject & other) override;

	bool isDead() { return enemyState.dead; };

private:
	void setCurrentAnimationInfo(float deltaTime);
	void throwRock();

public:
	sf::Vector2f startingPosition;

private:
	typedef struct state {
		bool attacking;
		bool throwing;
		bool walking;
		bool hurt;
		bool idle;
		bool dead;
	} state;
	state enemyState;
	sf::Vector2f velocity;
	bool canAttack;
	bool canThrow;
	float speedMultiplier;
	float acceleration;
	float maxSpeed;
	float timeBetweenThrows;
	float timePassedSinceLastThrow;

	bool movingRight;
	float orientationSign;
	float movingDistance;

	float spotPlayerDistance;
	float closeCombatDistance;
	int hpBar;
	float corpseShownTime;
	float deadTime;

	float totalIdleTime;
	float idleTime;
};

