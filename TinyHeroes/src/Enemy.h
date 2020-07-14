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

	bool isDead() { return m_enemyState.dead; };

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
	state m_enemyState;
	sf::Vector2f m_velocity;
	bool m_canAttack;
	bool m_canThrow;
	float m_speedMultiplier;
	float m_acceleration;
	float m_maxSpeed;
	float m_timeBetweenThrows;
	float m_timePassedSinceLastThrow;

	bool m_movingRight;
	float m_orientationSign;
	float m_movingDistance;

	float m_spotPlayerDistance;
	float m_closeCombatDistance;
	int m_hpBar;
	float m_corpseShownTime;
	float m_deadTime;

	float m_totalIdleTime;
	float m_idleTime;
};

