#include "Enemy.h"
#include "Renderer.h"
#include "Projectile.h"

Enemy::Enemy(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	m_canThrow = true;
	m_canAttack = true;
	m_enemyState.throwing = false;
	m_enemyState.attacking = false;
	m_enemyState.hurt = false;
	m_enemyState.idle = true;
	m_enemyState.dead = false;

	m_speedMultiplier = 1.0f;
	m_acceleration = 20.0f;
	m_maxSpeed = 100.0f;

	m_movingDistance = 150.0f;
	m_spotPlayerDistance = 300.0f;
	m_closeCombatDistance = 100.0f;

	m_totalIdleTime = 3.0f;
	m_idleTime = 0.0f;
	m_orientationSign = 1.0f;

	m_timeBetweenThrows = 1.5f;
	m_timePassedSinceLastThrow = 0.0f;

	m_hpBar = 3;
	m_corpseShownTime = 3.0f;
	m_deadTime = 0.0f;

	startingPosition = sf::Vector2f(400.0f, 400.0f);
}

Enemy::~Enemy()
{
}

void Enemy::render()
{
	Renderer::getInstance().getWindow().draw(m_sprite);
}

void Enemy::update(float deltaTime)
{
	if (!m_canThrow)
		m_enemyState.throwing = true;
	if (!m_canAttack)
		m_enemyState.attacking = true;

	m_timePassedSinceLastThrow += deltaTime;
	sf::Vector2f currentPosition = m_sprite.getPosition();

	if (!m_enemyState.dead)
	{
		if (abs(currentPosition.x - WorldInstance::getInstance().getPlayerPosition().x) <= m_spotPlayerDistance)
		{
			if (abs(currentPosition.x - WorldInstance::getInstance().getPlayerPosition().x) <= m_closeCombatDistance)
			{
				m_enemyState.attacking = true;
			}
			else if (m_timePassedSinceLastThrow - m_timeBetweenThrows >= 0.0f)
			{
				m_timePassedSinceLastThrow = 0.0f;
				m_enemyState.throwing = true;
			}
			(currentPosition.x - WorldInstance::getInstance().getPlayerPosition().x) > 0.0f ? 
				m_animation.setAnimationFaceRight(false) : m_animation.setAnimationFaceRight(true);;

			m_orientationSign = 0.0f;
			m_velocity.x = 0.0f;
		}
		else
		{
			m_enemyState.attacking = false;
			m_enemyState.throwing = false;
			m_animation.setAnimationFaceRight(m_movingRight);
			m_orientationSign = m_movingRight ? 1.0f : -1.0f;
			if (abs(currentPosition.x - startingPosition.x) >= m_movingDistance)
			{
				m_enemyState.idle = true;
				m_enemyState.walking = false;
				startingPosition = currentPosition;
			}
			else if (m_enemyState.idle)
			{
				m_idleTime += deltaTime;
				m_orientationSign = 0.0f;
				m_velocity.x = 0.0f;
				if (m_idleTime >= m_totalIdleTime)
				{
					m_enemyState.idle = false;
					m_enemyState.walking = true;
					m_idleTime = 0.0f;

					m_movingRight = !m_movingRight;
					m_animation.setAnimationFaceRight(m_movingRight);
					m_orientationSign = m_movingRight ? 1.0f : -1.0f;
				}
			}
		}
	}

	m_velocity.x += m_acceleration * m_orientationSign;
	m_velocity.y += WorldInstance::getInstance().getGravity() * deltaTime; //adding gravity to go down

	if (abs(m_velocity.x) > m_maxSpeed)
	{
		m_velocity.x = m_maxSpeed * (m_velocity.x / abs(m_velocity.x));
	}

	setCurrentAnimationInfo(deltaTime);
	m_animation.update(deltaTime);
	move(m_velocity * deltaTime);
}

void Enemy::setCurrentAnimationInfo(float deltaTime)
{
	if (m_enemyState.dead)
	{
		setRenderDepth(0);
		m_deadTime += deltaTime;
		if (m_animation.m_currentImage >= 7)
		{	
			m_animation.m_currentImage = 6;
			if (m_deadTime >= m_corpseShownTime)
			{
				destroy();
			}
		}
		else
		{
			m_animation.setCurrentAnimationAs("dead");
			m_velocity.x = 0.0f;
		}
	}
	else if (m_enemyState.hurt)
	{
		if (m_animation.m_currentImage >= 8)
		{
			m_enemyState.hurt = false;
		}
		else
		{
			m_animation.setCurrentAnimationAs("hurt");
			m_velocity.x = 0.0f;
		}
	}
	else if (m_enemyState.attacking)
	{
		if (m_animation.m_currentImage >= 6)
		{
			m_enemyState.attacking = false;
			m_canAttack = true;
		}
		else
		{
			m_animation.setCurrentAnimationAs("attacking");
		}
	}
	else if (m_enemyState.throwing)
	{
		if (m_animation.m_currentImage >= 5)
		{
			throwRock();
			m_enemyState.throwing = false;
			m_canThrow = true;
			m_animation.m_currentImage = 0;
		}
		else
		{
			m_animation.setCurrentAnimationAs("throwing");
		}
	}
	else if (m_enemyState.walking)
	{
		m_animation.setCurrentAnimationAs("walking");
	}
	else
	{
		m_animation.setCurrentAnimationAs("idle");
	}
}

void Enemy::throwRock()
{
	sf::Vector2f position = m_sprite.getPosition();
	position.x += m_animation.isAnimationFacingRight() ? m_body.width : 0.0f;
	position.y += m_body.height / 3.0f;
	auto slashPosition = m_filePath.find_last_of('/');
	std::string folderPath = m_filePath.substr(0, slashPosition + 1);
	Projectile* rock = new Projectile(folderPath+"Rock.png", getRenderDepth(), m_velocity.x, position, m_animation.isAnimationFacingRight());
}

void Enemy::onCollision(CollisionObject & other)
{
	if (m_enemyState.dead)
	{
		if (m_intersectionRect.height < 0.0f && !dynamic_cast<Projectile*>(&other))
		{
			//collision on the bottom
			move(0.0f, m_intersectionRect.height);
			m_velocity.y = 0.0f;
		}
	}
	else if (dynamic_cast<Projectile*>(&other))
	{
		m_hpBar--;
		if (m_hpBar == 0)
		{
			m_enemyState.dead = true;
		}
		else
		{
			m_enemyState.hurt = true;
			m_timePassedSinceLastThrow = 0.0f;
			m_animation.m_currentImage = 0.0f; //do we want the animation to restart on every hit? probably yes
		}
	}
	else
	{
		if (m_intersectionRect.width < 0.0f || m_intersectionRect.width > 0.0f)
		{
			//collision on the left || right
			move(m_intersectionRect.width, 0.0f);
			m_velocity.x = 0.0f;
		}
		if (m_intersectionRect.height < 0.0f)
		{
			//collision on the bottom
			move(0.0f, m_intersectionRect.height);
			m_velocity.y = 0.0f;
		}
		else if (m_intersectionRect.height > 0.0f)
		{
			//collision on the top
			move(0.0f, m_intersectionRect.height);
			m_velocity.y = 0.0f;
		}
	}
}

void Enemy::onCollisionEnd(CollisionObject & other)
{
}
