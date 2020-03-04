#include "PlayerCharacter.h"
#include "Renderer.h"
#include "WorldInstance.h"

PlayerCharacter::PlayerCharacter(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	animation.currentAnimationInfo.faceRight = true;
	canJump = true;
	jumping = false;
	running = false;
	attacking = false;
	canAttack = true;
	acceleration = 20.0f;
	maxSpeed = 200.0f;
	jumpHeight = 100.0f;

	sf::Texture animationTexture;
	animationTexture.loadFromFile("Heroes/PinkMonster/Idle_4.png");
	animation.animationTextures.push_back(animationTexture);
	animationTexture.loadFromFile("Heroes/PinkMonster/Walk_6.png");
	animation.animationTextures.push_back(animationTexture);
	animationTexture.loadFromFile("Heroes/PinkMonster/Run_6.png");
	animation.animationTextures.push_back(animationTexture);
	animationTexture.loadFromFile("Heroes/PinkMonster/Jump_8.png");
	animation.animationTextures.push_back(animationTexture);
	animationTexture.loadFromFile("Heroes/PinkMonster/Throw_4.png");
	animation.animationTextures.push_back(animationTexture);

	sprite.setPosition(0.0f, 400.0f);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;
	setScale(sf::Vector2f(3.0f, 3.0f));
}


PlayerCharacter::~PlayerCharacter()
{
	
}

void PlayerCharacter::update(float deltaTime)
{
	float runningSwitchTime = 0.1f;
	float walkingSwitchTime = 0.25f;
	float jumpingSwitchTime = 0.2f;
	float idleSwitchTime = 0.3f;
	float attackSwitchTime = 0.08f;

	attacking = false;
	if (!canAttack)
		attacking = true;

	jumping = false;
	if (!canJump)
		jumping = true;
	running = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jumping = true;
		if (canJump)
		{
			canJump = false;
			//square root( 2.0f * gravity * jumpHeight)
			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
			animation.currentAnimationInfo.currentImage = 0;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		attacking = true;
		if (canAttack)
		{
			canAttack = false;
			animation.currentAnimationInfo.currentImage = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= acceleration;
		animation.currentAnimationInfo.animationIndex = 1;
		animation.currentAnimationInfo.imageCount = 6;
		animation.currentAnimationInfo.switchTime = walkingSwitchTime;
		animation.currentAnimationInfo.faceRight = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			running = true;
			velocity.x -= acceleration;
			animation.currentAnimationInfo.animationIndex = 2;
			animation.currentAnimationInfo.imageCount = 6;
			animation.currentAnimationInfo.switchTime = runningSwitchTime;
		}
		if (jumping)
		{
			animation.currentAnimationInfo.animationIndex = 3;
			animation.currentAnimationInfo.imageCount = 8;
			animation.currentAnimationInfo.switchTime = jumpingSwitchTime;
		}
		if (attacking)
		{
			if (animation.currentAnimationInfo.currentImage >= 3)
			{
				attacking = false;
				canAttack = true;
			}
			else
			{
				animation.currentAnimationInfo.animationIndex = 4;
				animation.currentAnimationInfo.imageCount = 4;
				animation.currentAnimationInfo.switchTime = attackSwitchTime;
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += acceleration;
		animation.currentAnimationInfo.animationIndex = 1;
		animation.currentAnimationInfo.imageCount = 6;
		animation.currentAnimationInfo.switchTime = walkingSwitchTime;
		animation.currentAnimationInfo.faceRight = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			running = true;
			velocity.x += acceleration;
			animation.currentAnimationInfo.animationIndex = 2;
			animation.currentAnimationInfo.imageCount = 6;
			animation.currentAnimationInfo.switchTime = runningSwitchTime;
		}
		if (jumping)
		{
			animation.currentAnimationInfo.animationIndex = 3;
			animation.currentAnimationInfo.imageCount = 8;
			animation.currentAnimationInfo.switchTime = jumpingSwitchTime;
		}
		if (attacking)
		{
			if (animation.currentAnimationInfo.currentImage >= 3)
			{
				attacking = false;
				canAttack = true;
			}
			else
			{
				animation.currentAnimationInfo.animationIndex = 4;
				animation.currentAnimationInfo.imageCount = 4;
				animation.currentAnimationInfo.switchTime = attackSwitchTime;
			}
		}
	}
	else if (jumping)
	{
		animation.currentAnimationInfo.animationIndex = 3;
		animation.currentAnimationInfo.imageCount = 8;
		animation.currentAnimationInfo.switchTime = jumpingSwitchTime;
	}
	else if (attacking)
	{
		if (animation.currentAnimationInfo.currentImage >= 3)
		{
			attacking = false;
			canAttack = true;
		}
		else
		{
			animation.currentAnimationInfo.animationIndex = 4;
			animation.currentAnimationInfo.imageCount = 4;
			animation.currentAnimationInfo.switchTime = attackSwitchTime;
		}
	}
	else
	{
		velocity.x = 0.0f; //insta stop moving when key isnt pressed
		//velocity.x *= 0.0f; //slowly stop moving (higher number=slower stop time, lower number=faster stop time)

		animation.currentAnimationInfo.animationIndex = 0;
		animation.currentAnimationInfo.imageCount = 4;
		animation.currentAnimationInfo.switchTime = idleSwitchTime;
	}

	velocity.y += 981.0f * deltaTime; //adding gravity to go down

	if (abs(velocity.x) > maxSpeed)
	{
		if (!running)
		{
			velocity.x = maxSpeed * (velocity.x / abs(velocity.x));
		}
		else
		{
			velocity.x = abs(velocity.x) > 2.0f * maxSpeed ? 2.0f * maxSpeed * (velocity.x / abs(velocity.x)) : velocity.x;
		}
	}
	if (sprite.getPosition().y >
		(Renderer::getInstance().getView().getCenter().y + Renderer::getInstance().getView().getSize().y / 2.0f))
	{
		//stop moving when player falls through the ground
		velocity.x = 0.0f;
	}

	animation.update(deltaTime);
	sprite.setTextureRect(animation.uvRect);
	sprite.setTexture(animation.animationTextures[animation.currentAnimationInfo.animationIndex]);
	sprite.move(velocity * deltaTime);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;

	WorldInstance::getInstance().setWorldSpeed(velocity.x);
}

void PlayerCharacter::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void PlayerCharacter::onCollision(CollisionObject & other)
{
	if (intersectionRect.width < 0.0f)
	{
		//collision on the left
		sprite.move(intersectionRect.width, 0.0f);
		body.left = sprite.getPosition().x;
		velocity.x = 0.0f;
	}
	else if (intersectionRect.width > 0.0f)
	{
		//collision on the right
		sprite.move(intersectionRect.width, 0.0f);
		body.left = sprite.getPosition().x;
		velocity.x = 0.0f;
	}

	if (intersectionRect.height < 0.0f)
	{
		//collision on the bottom
		sprite.move(0.0f, intersectionRect.height);
		body.top = sprite.getPosition().y;
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (intersectionRect.height > 0.0f)
	{
		//collision on the top
		sprite.move(0.0f, intersectionRect.height);
		body.top = sprite.getPosition().y;
		velocity.y = 0.0f;
	}
}