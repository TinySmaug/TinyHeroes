#include "PlayerCharacter.h"

//#include <iostream>

PlayerCharacter::PlayerCharacter(std::string texturePath)
	: Entity(texturePath), animation()
{
	animation.info.faceRight = true;
	canJump = true;
	jumping = false;
	running = false;
	acceleration = 30.0f;
	maxSpeed = 300.0f;
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

	sprite.setPosition(100.0f, 470.0f);
	sprite.setScale(sf::Vector2f(3.0f, 3.0f));
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
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= acceleration;
		animation.info.animationIndex = 1;
		animation.info.imageCount = 6;
		animation.info.switchTime = walkingSwitchTime;
		animation.info.faceRight = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			running = true;
			velocity.x -= acceleration;
			animation.info.animationIndex = 2;
			animation.info.imageCount = 6;
			animation.info.switchTime = runningSwitchTime;
		}
		if (jumping)
		{
			animation.info.animationIndex = 3;
			animation.info.imageCount = 8;
			animation.info.switchTime = jumpingSwitchTime;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += acceleration;
		animation.info.animationIndex = 1;
		animation.info.imageCount = 6;
		animation.info.switchTime = walkingSwitchTime;
		animation.info.faceRight = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			running = true;
			velocity.x += acceleration;
			animation.info.animationIndex = 2;
			animation.info.imageCount = 6;
			animation.info.switchTime = runningSwitchTime;
		}
		if (jumping)
		{
			animation.info.animationIndex = 3;
			animation.info.imageCount = 8;
			animation.info.switchTime = jumpingSwitchTime;
		}
	}
	else if (jumping)
	{
		animation.info.animationIndex = 3;
		animation.info.imageCount = 8;
		animation.info.switchTime = jumpingSwitchTime;
	}
	else
	{
		velocity.x = 0.0f; //insta stop moving when key isnt pressed
		//velocity.x *= 0.0f; //slowly stop moving (higher number=slower stop time, lower number=faster stop time)
		
		animation.info.animationIndex = 0;
		animation.info.imageCount = 4;
		animation.info.switchTime = idleSwitchTime;
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
	
	//std::cout << velocity.x << std::endl;

	animation.update(deltaTime);
	sprite.setTextureRect(animation.uvRect);
	sprite.setTexture(animation.animationTextures[animation.info.animationIndex]);
	sprite.move(velocity * deltaTime);

	//remove after implementing collisions
	if (sprite.getPosition().y > 470.0f)
	{
		velocity.y = 0.0f;
		sprite.setPosition(sprite.getPosition().x, 470.0f);
		jumping = false;
		canJump = true;
	}
}

