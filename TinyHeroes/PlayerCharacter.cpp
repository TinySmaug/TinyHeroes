#include "PlayerCharacter.h"

#include <iostream>

PlayerCharacter::PlayerCharacter(std::string texturePath)
	: Entity(texturePath), animation(0.25f)
{
	faceRight = true;
	canJump = true;
	acceleration = 100.0f;
	maxSpeed = 700.0f;
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
	float runningMultiplier =  1.3f;
	float jumpingMultiplier =  1.5f;

	velocity.x = 0.0f; //insta stop moving when key isnt pressed
	//velocity.x *= 0.0f; //slowly stop moving (higher number=slower stop time, lower number=faster stop time)

	bool jumping = false;
	if (!canJump)
		jumping = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= acceleration;
		animationIndex = 1;
		imageCount = 6;
		faceRight = false;
		if (jumping)
		{
			animationIndex = 3;
			imageCount = 8;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += acceleration;
		animationIndex = 1;
		imageCount = 6;
		faceRight = true;
		if (jumping)
		{
			animationIndex = 3;
			imageCount = 8;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		deltaTime *= runningMultiplier;
		velocity.x -= acceleration;
		animationIndex = 2;
		imageCount = 6;
		faceRight = false;
		if (jumping)
		{
			animationIndex = 3;
			imageCount = 8;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		deltaTime *= runningMultiplier;
		velocity.x += acceleration;
		animationIndex = 2;
		imageCount = 6;
		faceRight = true;
		if (jumping)
		{
			animationIndex = 3;
			imageCount = 8;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jumping = true;
		deltaTime *= jumpingMultiplier;

		if (canJump)
		{
			canJump = false;
			//square root( 2.0f * gravity * jumpHeight)
			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
			animationIndex = 3;
			imageCount = 8;
		}
	}
	
	velocity.y += 981.0f * deltaTime; //adding gravity to go down
	
	if (velocity.x == 0.0f)
	{
		if (jumping == true)
		{
			animationIndex = 3;
			imageCount = 8;
		}
		else
		{
			animationIndex = 0;
			imageCount = 4;
		}
	}

	if (abs(velocity.x) > maxSpeed)
	{
		velocity.x = maxSpeed * (velocity.x / abs(velocity.x));
	}
	
	//std::cout << velocity.x << std::endl;

	animation.update(animationIndex, imageCount, deltaTime, faceRight);
	sprite.setTextureRect(animation.uvRect);
	sprite.setTexture(animation.animationTextures[animationIndex]);
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

