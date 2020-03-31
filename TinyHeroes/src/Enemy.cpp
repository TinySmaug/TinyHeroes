#include "Enemy.h"
#include "Renderer.h"
#include "Projectile.h"

Enemy::Enemy(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	canThrow = true;
	canAttack = true;
	enemyState.throwing = false;
	enemyState.attacking = false;
	enemyState.hurt = false;
	enemyState.idle = true;
	enemyState.dead = false;

	speedMultiplier = 1.0f;
	acceleration = 20.0f;
	maxSpeed = 100.0f;

	movingDistance = 150.0f;
	spotPlayerDistance = 300.0f;
	closeCombatDistance = 100.0f;

	totalIdleTime = 3.0f;
	idleTime = 0.0f;
	orientationSign = 1.0f;

	timeBetweenThrows = 1.5f;
	timePassedSinceLastThrow = 0.0f;

	hpBar = 3;
	corpseShownTime = 3.0f;
	deadTime = 0.0f;

	startingPosition = sf::Vector2f(400.0f, 400.0f);
}

Enemy::~Enemy()
{
}

void Enemy::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void Enemy::update(float deltaTime)
{
	if (!canThrow)
		enemyState.throwing = true;
	if (!canAttack)
		enemyState.attacking = true;

	timePassedSinceLastThrow += deltaTime;
	sf::Vector2f currentPosition = sprite.getPosition();

	if (!enemyState.dead)
	{
		if (abs(currentPosition.x - WorldInstance::getInstance().getPlayerPosition().x) <= spotPlayerDistance)
		{
			if (abs(currentPosition.x - WorldInstance::getInstance().getPlayerPosition().x) <= closeCombatDistance)
			{
				enemyState.attacking = true;
			}
			else if (timePassedSinceLastThrow - timeBetweenThrows >= 0.0f)
			{
				timePassedSinceLastThrow = 0.0f;
				enemyState.throwing = true;
			}
			(currentPosition.x - WorldInstance::getInstance().getPlayerPosition().x) > 0.0f ? 
				animation.setAnimationFaceRight(false) : animation.setAnimationFaceRight(true);;

			orientationSign = 0.0f;
			velocity.x = 0.0f;
		}
		else
		{
			enemyState.attacking = false;
			enemyState.throwing = false;
			animation.setAnimationFaceRight(movingRight);
			orientationSign = movingRight ? 1.0f : -1.0f;
			if (abs(currentPosition.x - startingPosition.x) >= movingDistance)
			{
				enemyState.idle = true;
				enemyState.walking = false;
				startingPosition = currentPosition;
			}
			else if (enemyState.idle)
			{
				idleTime += deltaTime;
				orientationSign = 0.0f;
				velocity.x = 0.0f;
				if (idleTime >= totalIdleTime)
				{
					enemyState.idle = false;
					enemyState.walking = true;
					idleTime = 0.0f;

					movingRight = !movingRight;
					animation.setAnimationFaceRight(movingRight);
					orientationSign = movingRight ? 1.0f : -1.0f;
				}
			}
		}
	}

	velocity.x += acceleration * orientationSign;
	velocity.y += WorldInstance::getInstance().getGravity() * deltaTime; //adding gravity to go down

	if (abs(velocity.x) > maxSpeed)
	{
		velocity.x = maxSpeed * (velocity.x / abs(velocity.x));
	}

	setCurrentAnimationInfo(deltaTime);
	animation.update(deltaTime);
	move(velocity * deltaTime);
}

void Enemy::setCurrentAnimationInfo(float deltaTime)
{
	if (enemyState.dead)
	{
		setRenderDepth(0);
		deadTime += deltaTime;
		if (animation.currentImage >= 7)
		{	
			animation.currentImage = 6;
			if (deadTime >= corpseShownTime)
			{
				destroy();
			}
		}
		else
		{
			animation.setCurrentAnimationAs("dead");
			velocity.x = 0.0f;
		}
	}
	else if (enemyState.hurt)
	{
		if (animation.currentImage >= 8)
		{
			enemyState.hurt = false;
		}
		else
		{
			animation.setCurrentAnimationAs("hurt");
			velocity.x = 0.0f;
		}
	}
	else if (enemyState.attacking)
	{
		if (animation.currentImage >= 6)
		{
			enemyState.attacking = false;
			canAttack = true;
		}
		else
		{
			animation.setCurrentAnimationAs("attacking");
		}
	}
	else if (enemyState.throwing)
	{
		if (animation.currentImage >= 5)
		{
			throwRock();
			enemyState.throwing = false;
			canThrow = true;
			animation.currentImage = 0;
		}
		else
		{
			animation.setCurrentAnimationAs("throwing");
		}
	}
	else if (enemyState.walking)
	{
		animation.setCurrentAnimationAs("walking");
	}
	else
	{
		animation.setCurrentAnimationAs("idle");
	}
}

void Enemy::throwRock()
{
	sf::Vector2f position = sprite.getPosition();
	position.x += animation.isAnimationFacingRight() ? body.width : 0.0f;
	position.y += body.height / 3.0f;
	auto slashPosition = filePath.find_last_of('/');
	std::string folderPath = filePath.substr(0, slashPosition + 1);
	Projectile* rock = new Projectile(folderPath+"Rock.png", getRenderDepth(), velocity.x, position, animation.isAnimationFacingRight());
}

void Enemy::onCollision(CollisionObject & other)
{
	if (enemyState.dead)
	{
		if (intersectionRect.height < 0.0f && !dynamic_cast<Projectile*>(&other))
		{
			//collision on the bottom
			move(0.0f, intersectionRect.height);
			velocity.y = 0.0f;
		}
	}
	else if (dynamic_cast<Projectile*>(&other))
	{
		hpBar--;
		if (hpBar == 0)
		{
			enemyState.dead = true;
		}
		else
		{
			enemyState.hurt = true;
			timePassedSinceLastThrow = 0.0f;
			animation.currentImage = 0.0f; //do we want the animation to restart on every hit? probably yes
		}
	}
	else
	{
		if (intersectionRect.width < 0.0f || intersectionRect.width > 0.0f)
		{
			//collision on the left || right
			move(intersectionRect.width, 0.0f);
			velocity.x = 0.0f;
		}
		if (intersectionRect.height < 0.0f)
		{
			//collision on the bottom
			move(0.0f, intersectionRect.height);
			velocity.y = 0.0f;
		}
		else if (intersectionRect.height > 0.0f)
		{
			//collision on the top
			move(0.0f, intersectionRect.height);
			velocity.y = 0.0f;
		}
	}
}

void Enemy::onCollisionEnd(CollisionObject & other)
{
}
