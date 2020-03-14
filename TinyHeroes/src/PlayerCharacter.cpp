#include "PlayerCharacter.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include "Projectile.h"
#include "InputManager.h"


PlayerCharacter::PlayerCharacter(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	animation.currentAnimationInfo.faceRight = true;
	canJump = true;
	canThrow = true;
	canAttack = true;
	canWalkAttack = true;
	playerState.jumping = false;
	playerState.running = false;
	playerState.throwing = false;
	playerState.pushing = false;
	playerState.attacking = false;
	playerState.walkAttack = false;
	speedMultiplier = 1.0f;
	acceleration = 50.0f;
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
	animationTexture.loadFromFile("Heroes/PinkMonster/Push_6.png");
	animation.animationTextures.push_back(animationTexture);
	animationTexture.loadFromFile("Heroes/PinkMonster/Attack_6.png");
	animation.animationTextures.push_back(animationTexture);
	animationTexture.loadFromFile("Heroes/PinkMonster/WalkAttack_6.png");
	animation.animationTextures.push_back(animationTexture);
}


PlayerCharacter::~PlayerCharacter()
{
}

PlayerCharacter & PlayerCharacter::operator=(PlayerCharacter & other)
{
	return other;
}

void PlayerCharacter::update(float deltaTime)
{
	if (!canThrow)
		playerState.throwing = true;
	if (!canJump)
		playerState.jumping = true;
	if (!canAttack)
		playerState.attacking = true;
	if (!canWalkAttack)
		playerState.walkAttack = true;
	if (intersectionRect.height == 0.0f)
	{
		playerState.pushing = false;
	}
	
	setCurrentAnimationInfo();
	
	velocity.y += WorldInstance::getInstance().getGravity() * deltaTime; //adding gravity to go down

	if (abs(velocity.x) > maxSpeed)
	{
		if (!playerState.running)
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
	move(velocity * deltaTime);

	WorldInstance::getInstance().setWorldSpeed(velocity.x);
}

void PlayerCharacter::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void PlayerCharacter::onCollision(CollisionObject & other)
{
	if (dynamic_cast<Projectile*>(&other))
	{
		//set hurt texture
	}
	else
	{
		if (intersectionRect.width < 0.0f || intersectionRect.width > 0.0f)
		{
			//collision on the left || right
			playerState.pushing = true;
		}

		if (intersectionRect.height < 0.0f)
		{
			//collision on the bottom
			move(0.0f, intersectionRect.height);
			velocity.y = 0.0f;
			canJump = true;
			playerState.jumping = false;
		}
		else if (intersectionRect.height > 0.0f)
		{
			//collision on the top
			move(0.0f, intersectionRect.height);
			velocity.y = 0.0f;
		}
	}
}

void PlayerCharacter::addInputHandlerFunctions()
{
	InputManager::InputHandlerData tmp;

	tmp.ActivationHandler = std::bind(&PlayerCharacter::handleLeftMouseButtonClick, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&PlayerCharacter::handleLeftMouseButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addMouseInputHandler(sf::Mouse::Button::Left, tmp);

	tmp.ActivationHandler = std::bind(&PlayerCharacter::handleRightMouseButtonClick, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&PlayerCharacter::handleRightMouseButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addMouseInputHandler(sf::Mouse::Button::Right, tmp);

	tmp.ActivationHandler = std::bind(&PlayerCharacter::handleAKeyboardButtonPressed, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&PlayerCharacter::handleAKeyboardButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addKeyboardInputHandler(sf::Keyboard::A, tmp);

	tmp.ActivationHandler = std::bind(&PlayerCharacter::handleDKeyboardButtonPressed, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&PlayerCharacter::handleDKeyboardButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addKeyboardInputHandler(sf::Keyboard::D, tmp);

	tmp.ActivationHandler = std::bind(&PlayerCharacter::handleSpaceKeyboardButtonPressed, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&PlayerCharacter::handleSpaceKeyboardButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addKeyboardInputHandler(sf::Keyboard::Space, tmp);

	tmp.ActivationHandler = std::bind(&PlayerCharacter::handleLShiftKeyboardButtonPressed, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&PlayerCharacter::handleLShiftKeyboardButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addKeyboardInputHandler(sf::Keyboard::LShift, tmp);
}

void PlayerCharacter::removeInputHandlerFunctions()
{
	InputManager::getInstance().removeMouseInputHandler(sf::Mouse::Button::Left);
	InputManager::getInstance().removeMouseInputHandler(sf::Mouse::Button::Right);

	InputManager::getInstance().removeKeyboardInputHandler(sf::Keyboard::A);
	InputManager::getInstance().removeKeyboardInputHandler(sf::Keyboard::D);
	InputManager::getInstance().removeKeyboardInputHandler(sf::Keyboard::Space);
	InputManager::getInstance().removeKeyboardInputHandler(sf::Keyboard::LShift);
}

void PlayerCharacter::setCurrentAnimationInfo()
{
	float runningSwitchTime = 0.1f;
	float walkingSwitchTime = 0.25f;
	float jumpingSwitchTime = 0.2f;
	float idleSwitchTime = 0.3f;
	float throwSwitchTime = 0.08f;
	float pushSwitchTime = 0.1f;
	float attackSwitchTime = 0.2f;
	float walkAttackSwitchTime = 0.2f;

	if (playerState.attacking)
	{
		if (animation.currentAnimationInfo.currentImage >= 5)
		{
			playerState.attacking = false;
			canAttack = true;
		}
		else
		{
			animation.currentAnimationInfo.animationIndex = 6;
			animation.currentAnimationInfo.imageCount = 6;
			animation.currentAnimationInfo.switchTime = attackSwitchTime;
		}
	}
	else if (playerState.throwing)
	{
		if (animation.currentAnimationInfo.currentImage >= 3)
		{
			playerState.throwing = false;
			canThrow = true;
		}
		else
		{
			animation.currentAnimationInfo.animationIndex = 4;
			animation.currentAnimationInfo.imageCount = 4;
			animation.currentAnimationInfo.switchTime = throwSwitchTime;
		}
	}
	else if (playerState.jumping)
	{
		animation.currentAnimationInfo.animationIndex = 3;
		animation.currentAnimationInfo.imageCount = 8;
		animation.currentAnimationInfo.switchTime = jumpingSwitchTime;
	}
	else if (playerState.pushing)
	{
		animation.currentAnimationInfo.animationIndex = 5;
		animation.currentAnimationInfo.imageCount = 6;
		animation.currentAnimationInfo.switchTime = pushSwitchTime;
	}
	else if (playerState.running)
	{
		animation.currentAnimationInfo.animationIndex = 2;
		animation.currentAnimationInfo.imageCount = 6;
		animation.currentAnimationInfo.switchTime = runningSwitchTime;
	}
	else if (playerState.walkAttack)
	{
		if (animation.currentAnimationInfo.currentImage >= 3)
		{
			playerState.walkAttack = false;
			canWalkAttack = true;
		}
		else
		{
			animation.currentAnimationInfo.animationIndex = 7;
			animation.currentAnimationInfo.imageCount = 6;
			animation.currentAnimationInfo.switchTime = walkAttackSwitchTime;
		}
	}
	else if (playerState.walking)
	{
		animation.currentAnimationInfo.animationIndex = 1;
		animation.currentAnimationInfo.imageCount = 6;
		animation.currentAnimationInfo.switchTime = walkingSwitchTime;
	}
	else
	{
		animation.currentAnimationInfo.animationIndex = 0;
		animation.currentAnimationInfo.imageCount = 4;
		animation.currentAnimationInfo.switchTime = idleSwitchTime;
	}
}

void PlayerCharacter::throwRock()
{
	sf::Vector2f position = sprite.getPosition();
	position.x += animation.currentAnimationInfo.faceRight ? body.width : 0.0f;
	position.y += body.height / 3.0f;
	Projectile* rock = new Projectile("World/Rock1.png", getRenderDepth(), velocity.x, position,
						   animation.currentAnimationInfo.faceRight);
}

void PlayerCharacter::handleLeftMouseButtonClick(float deltaTime)
{
	if (canThrow)
	{
		playerState.throwing = true;
		canThrow = false;
		animation.currentAnimationInfo.currentImage = 0;
		throwRock();
	}
}

void PlayerCharacter::handleRightMouseButtonClick(float deltaTime)
{
	if (playerState.walking && canWalkAttack)
	{
		playerState.walkAttack = true;
		canWalkAttack = false;
		animation.currentAnimationInfo.currentImage = 0;
	}
	else if (canAttack && !playerState.running && !playerState.walking)
	{
		playerState.attacking = true;
		animation.currentAnimationInfo.currentImage = 0;
	}
}

void PlayerCharacter::handleAKeyboardButtonPressed(float deltaTime)
{
	playerState.walking = true;
	velocity.x -= (acceleration * speedMultiplier);
	animation.currentAnimationInfo.faceRight = false;
}

void PlayerCharacter::handleDKeyboardButtonPressed(float deltaTime)
{
	playerState.walking = true;
	velocity.x += (acceleration * speedMultiplier);
	animation.currentAnimationInfo.faceRight = true;
}

void PlayerCharacter::handleSpaceKeyboardButtonPressed(float deltaTime)
{
	if (canJump)
	{
		playerState.jumping = true;
		canJump = false;
		//square root( 2.0f * gravity * jumpHeight)
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		animation.currentAnimationInfo.currentImage = 0;
	}
}

void PlayerCharacter::handleLShiftKeyboardButtonPressed(float deltaTime)
{
	if (playerState.walking && canJump)
	{
		speedMultiplier = 2.0f;
		playerState.running = true;
	}
}

void PlayerCharacter::handleLeftMouseButtonReleased(float deltaTime)
{

}

void PlayerCharacter::handleRightMouseButtonReleased(float deltaTime)
{

}

void PlayerCharacter::handleAKeyboardButtonReleased(float deltaTime)
{
	velocity.x = 0.0f; //insta stop moving when key isnt pressed
	//velocity.x *= 0.0f; //slowly stop moving (higher number=slower stop time, lower number=faster stop time)
	playerState.walking = false;
	playerState.running = false;
	playerState.pushing = false;
}

void PlayerCharacter::handleDKeyboardButtonReleased(float deltaTime)
{
	velocity.x = 0.0f;
	playerState.walking = false;
	playerState.running = false;
	playerState.pushing = false;
}

void PlayerCharacter::handleSpaceKeyboardButtonReleased(float deltaTime)
{

}

void PlayerCharacter::handleLShiftKeyboardButtonReleased(float deltaTime)
{
	speedMultiplier = 1.0f;
	playerState.running = false;
}