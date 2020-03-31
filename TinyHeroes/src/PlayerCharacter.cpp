#include "PlayerCharacter.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include "InputManager.h"

#include "Projectile.h"
#include "Enemy.h"

PlayerCharacter::PlayerCharacter(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
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
	playerState.hurt = false;
	speedMultiplier = 1.0f;
	acceleration = 50.0f;
	maxSpeed = 200.0f;
	jumpHeight = 100.0f;
}


PlayerCharacter::~PlayerCharacter()
{
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

	setCurrentAnimationInfo();
	animation.update(deltaTime);
	
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
		playerState.hurt = true;
	}
	else if (dynamic_cast<Enemy*>(&other))
	{
		if (!(dynamic_cast<Enemy*>(&other)->isDead()))
		{
			playerState.hurt = true;
		}
	}
	else if(other.isMovable())
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

void PlayerCharacter::onCollisionEnd(CollisionObject & other)
{
	if (other.isMovable())
	{
		playerState.pushing = false;
	}
	else
	{
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
	if (playerState.hurt)
	{
		if (animation.currentImage >= 3)
		{
			playerState.hurt = false;
			animation.currentImage = 0;
		}
		else
		{
			animation.setCurrentAnimationAs("hurt");
			velocity.x = 0.0f;
		}
	}
	else if (playerState.attacking)
	{
		if (animation.currentImage >= 5)
		{
			playerState.attacking = false;
			canAttack = true;
			animation.currentImage = 0;
		}
		else
		{
			animation.setCurrentAnimationAs("attacking");
			velocity.x = 0.0f;
		}
	}
	else if (playerState.throwing)
	{
		if (animation.currentImage >= 3)
		{
			playerState.throwing = false;
			canThrow = true;
			animation.currentImage = 0;
		}
		else
		{
			animation.setCurrentAnimationAs("throwing");
			velocity.x = 0.0f;
		}
	}
	else if (playerState.jumping)
	{
		animation.setCurrentAnimationAs("jumping");
	}
	else if (playerState.pushing)
	{
		animation.setCurrentAnimationAs("pushing");
	}
	else if (playerState.running)
	{
		animation.setCurrentAnimationAs("running");
	}
	else if (playerState.walkAttack)
	{
		if (animation.currentImage >= 3)
		{
			playerState.walkAttack = false;
			canWalkAttack = true;
		}
		else
		{
			animation.setCurrentAnimationAs("walkAttack");
		}
	}
	else if (playerState.walking)
	{
		animation.setCurrentAnimationAs("walking");
	}
	else
	{
		animation.setCurrentAnimationAs("idle");
	}
}

void PlayerCharacter::throwRock()
{
	sf::Vector2f position = sprite.getPosition();
	position.x += animation.isAnimationFacingRight() ? body.width : 0.0f;
	position.y += body.height / 3.0f;
	Projectile* rock = new Projectile("Heroes/Rock.png", getRenderDepth(), velocity.x, position, animation.isAnimationFacingRight());
}

void PlayerCharacter::handleLeftMouseButtonClick(float deltaTime)
{
	if (canThrow)
	{
		playerState.throwing = true;
		canThrow = false;
		throwRock();
	}
}

void PlayerCharacter::handleRightMouseButtonClick(float deltaTime)
{
	if (playerState.walking && canWalkAttack && !playerState.running)
	{
		playerState.walkAttack = true;
		canWalkAttack = false;
	}
	else if (canAttack && !playerState.running && !playerState.walking)
	{
		playerState.attacking = true;
		canAttack = false;
	}
}

void PlayerCharacter::handleAKeyboardButtonPressed(float deltaTime)
{
	if (!movingRight)
	{
		playerState.walking = true;
		velocity.x -= (acceleration * speedMultiplier);
		animation.setAnimationFaceRight(false);
		movingLeft = true;
	}
}

void PlayerCharacter::handleDKeyboardButtonPressed(float deltaTime)
{
	if (!movingLeft)
	{
		playerState.walking = true;
		velocity.x += (acceleration * speedMultiplier);
		animation.setAnimationFaceRight(true);
		movingRight = true;
	}
}

void PlayerCharacter::handleSpaceKeyboardButtonPressed(float deltaTime)
{
	if (canJump)
	{
		playerState.jumping = true;
		canJump = false;
		//square root( 2.0f * gravity * jumpHeight)
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
}

void PlayerCharacter::handleLShiftKeyboardButtonPressed(float deltaTime)
{
	if (playerState.walking && canJump && !playerState.pushing)
	{
		speedMultiplier = 2.0f;
		playerState.running = true;
	}
	else if (playerState.pushing)
	{
		speedMultiplier = 1.0f;
		playerState.running = false;
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
	movingLeft = false;
}

void PlayerCharacter::handleDKeyboardButtonReleased(float deltaTime)
{
	velocity.x = 0.0f;
	playerState.walking = false;
	playerState.running = false;
	movingRight = false;
}

void PlayerCharacter::handleSpaceKeyboardButtonReleased(float deltaTime)
{

}

void PlayerCharacter::handleLShiftKeyboardButtonReleased(float deltaTime)
{
	speedMultiplier = 1.0f;
	playerState.running = false;
}