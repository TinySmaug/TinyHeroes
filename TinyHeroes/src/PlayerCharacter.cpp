#include "PlayerCharacter.h"

//#include <iostream>

PlayerCharacter::PlayerCharacter(std::string texturePath, Renderer &renderer, WorldInstance& world, int depth)
	: Entity(texturePath, renderer, world)
{
	this->depth = depth;
	animation.info.faceRight = true;
	canJump = true;
	jumping = false;
	running = false;
	attacking = false;
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
	sprite.setScale(sf::Vector2f(3.0f, 3.0f));
	body.height *= 3.0f;
	body.width *= 3.0f;
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
		animation.info.currentImage = 0;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		attacking = true;
		animation.info.currentImage = 0;
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
		if (attacking)
		{
			if (animation.info.currentImage >= 3)
			{
				attacking = false;
			}
			else
			{
				animation.info.animationIndex = 4;
				animation.info.imageCount = 4;
				animation.info.switchTime = attackSwitchTime;
			}
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
		if (attacking)
		{
			if (animation.info.currentImage >= 3)
			{
				attacking = false;
			}
			else
			{
				animation.info.animationIndex = 4;
				animation.info.imageCount = 4;
				animation.info.switchTime = attackSwitchTime;
			}
		}
	}
	else if (jumping)
	{
		animation.info.animationIndex = 3;
		animation.info.imageCount = 8;
		animation.info.switchTime = jumpingSwitchTime;
	}
	else if (attacking)
	{
		if (animation.info.currentImage >= 3)
		{
			attacking = false;
		}
		else
		{
			animation.info.animationIndex = 4;
			animation.info.imageCount = 4;
			animation.info.switchTime = attackSwitchTime;
		}
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
	
	animation.update(deltaTime);
	sprite.setTextureRect(animation.uvRect);
	sprite.setTexture(animation.animationTextures[animation.info.animationIndex]);
	sprite.move(velocity * deltaTime);
	body.left = sprite.getPosition().x;
	body.top = sprite.getPosition().y;	
}

void PlayerCharacter::render(sf::RenderWindow & window)
{
	window.draw(sprite);
}

void PlayerCharacter::onCollision(CollisionObject & other, sf::Vector2f& direction, sf::FloatRect& intersectionRect)
{
	if (direction.x < 0.0f)
	{
		//collision on the left
		sprite.move(-intersectionRect.width, 0.0f);
		body.left = sprite.getPosition().x;
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision on the right
		sprite.move(intersectionRect.width, 0.0f);
		body.left = sprite.getPosition().x;
		velocity.x = 0.0f;
	}

	if (direction.y < 0.0f)
	{
		//collision on the bottom
		sprite.move(0.0f, -intersectionRect.height);
		body.top = sprite.getPosition().y;
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//collision on the top
		sprite.move(0.0f, intersectionRect.height);
		body.top = sprite.getPosition().y;
		velocity.y = 0.0f;
	}
}