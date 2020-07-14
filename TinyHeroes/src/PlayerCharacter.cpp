#include "PlayerCharacter.h"
#include "Renderer.h"
#include "WorldInstance.h"
#include "InputManager.h"

#include "Projectile.h"
#include "Enemy.h"

PlayerCharacter::PlayerCharacter(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	m_canJump = true;
	m_canThrow = true;
	m_canAttack = true;
	m_canWalkAttack = true;
	m_playerState.jumping = false;
	m_playerState.running = false;
	m_playerState.throwing = false;
	m_playerState.pushing = false;
	m_playerState.attacking = false;
	m_playerState.walkAttack = false;
	m_playerState.hurt = false;
	m_speedMultiplier = 1.0f;
	m_acceleration = 50.0f;
	m_maxSpeed = 200.0f;
	m_jumpHeight = 100.0f;
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::update(float deltaTime)
{
	if (!m_canThrow)
		m_playerState.throwing = true;
	if (!m_canJump)
		m_playerState.jumping = true;
	if (!m_canAttack)
		m_playerState.attacking = true;
	if (!m_canWalkAttack)
		m_playerState.walkAttack = true;
	
	m_velocity.y += WorldInstance::getInstance().getGravity() * deltaTime; //adding gravity to go down

	if (abs(m_velocity.x) > m_maxSpeed)
	{
		if (!m_playerState.running)
		{
			m_velocity.x = m_maxSpeed * (m_velocity.x / abs(m_velocity.x));
		}
		else
		{
			m_velocity.x = abs(m_velocity.x) > 2.0f * m_maxSpeed ? 2.0f * m_maxSpeed * (m_velocity.x / abs(m_velocity.x)) : m_velocity.x;
		}
	}
	if (m_sprite.getPosition().y >
		(Renderer::getInstance().getView().getCenter().y + Renderer::getInstance().getView().getSize().y / 2.0f))
	{
		//stop moving when player falls through the ground
		m_velocity.x = 0.0f;
	}

	setCurrentAnimationInfo();
	m_animation.update(deltaTime);
	
	move(m_velocity * deltaTime);

	WorldInstance::getInstance().setWorldSpeed(m_velocity.x);
}

void PlayerCharacter::render()
{
	Renderer::getInstance().getWindow().draw(m_sprite);
}

void PlayerCharacter::onCollision(CollisionObject & other)
{
	if (dynamic_cast<Projectile*>(&other))
	{
		m_playerState.hurt = true;
	}
	else if (dynamic_cast<Enemy*>(&other))
	{
		if (!(dynamic_cast<Enemy*>(&other)->isDead()))
		{
			m_playerState.hurt = true;
		}
	}
	else if(other.isMovable())
	{
		if (m_intersectionRect.width < 0.0f || m_intersectionRect.width > 0.0f)
		{
			//collision on the left || right
			m_playerState.pushing = true;
		}
		if (m_intersectionRect.height < 0.0f)
		{
			//collision on the bottom
			move(0.0f, m_intersectionRect.height);
			m_velocity.y = 0.0f;
			m_canJump = true;
			m_playerState.jumping = false;
		}
		else if (m_intersectionRect.height > 0.0f)
		{
			//collision on the top
			move(0.0f, m_intersectionRect.height);
			m_velocity.y = 0.0f;
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
			m_canJump = true;
			m_playerState.jumping = false;
		}
		else if (m_intersectionRect.height > 0.0f)
		{
			//collision on the top
			move(0.0f, m_intersectionRect.height);
			m_velocity.y = 0.0f;
		}
	}
}

void PlayerCharacter::onCollisionEnd(CollisionObject & other)
{
	if (other.isMovable())
	{
		m_playerState.pushing = false;
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
	if (m_playerState.hurt)
	{
		if (m_animation.m_currentImage >= 3)
		{
			m_playerState.hurt = false;
			m_animation.m_currentImage = 0;
		}
		else
		{
			m_animation.setCurrentAnimationAs("hurt");
			m_velocity.x = 0.0f;
		}
	}
	else if (m_playerState.attacking)
	{
		if (m_animation.m_currentImage >= 5)
		{
			m_playerState.attacking = false;
			m_canAttack = true;
			m_animation.m_currentImage = 0;
		}
		else
		{
			m_animation.setCurrentAnimationAs("attacking");
			m_velocity.x = 0.0f;
		}
	}
	else if (m_playerState.throwing)
	{
		if (m_animation.m_currentImage >= 3)
		{
			m_playerState.throwing = false;
			m_canThrow = true;
			m_animation.m_currentImage = 0;
		}
		else
		{
			m_animation.setCurrentAnimationAs("throwing");
			m_velocity.x = 0.0f;
		}
	}
	else if (m_playerState.jumping)
	{
		m_animation.setCurrentAnimationAs("jumping");
	}
	else if (m_playerState.pushing)
	{
		m_animation.setCurrentAnimationAs("pushing");
	}
	else if (m_playerState.running)
	{
		m_animation.setCurrentAnimationAs("running");
	}
	else if (m_playerState.walkAttack)
	{
		if (m_animation.m_currentImage >= 3)
		{
			m_playerState.walkAttack = false;
			m_canWalkAttack = true;
		}
		else
		{
			m_animation.setCurrentAnimationAs("walkAttack");
		}
	}
	else if (m_playerState.walking)
	{
		m_animation.setCurrentAnimationAs("walking");
	}
	else
	{
		m_animation.setCurrentAnimationAs("idle");
	}
}

void PlayerCharacter::throwRock()
{
	sf::Vector2f position = m_sprite.getPosition();
	position.x += m_animation.isAnimationFacingRight() ? m_body.width : 0.0f;
	position.y += m_body.height / 3.0f;
	Projectile* rock = new Projectile("Heroes/Rock.png", getRenderDepth(), m_velocity.x, position, m_animation.isAnimationFacingRight());
}

void PlayerCharacter::handleLeftMouseButtonClick(float deltaTime)
{
	if (m_canThrow)
	{
		m_playerState.throwing = true;
		m_canThrow = false;
		throwRock();
	}
}

void PlayerCharacter::handleRightMouseButtonClick(float deltaTime)
{
	if (m_playerState.walking && m_canWalkAttack && !m_playerState.running)
	{
		m_playerState.walkAttack = true;
		m_canWalkAttack = false;
	}
	else if (m_canAttack && !m_playerState.running && !m_playerState.walking)
	{
		m_playerState.attacking = true;
		m_canAttack = false;
	}
}

void PlayerCharacter::handleAKeyboardButtonPressed(float deltaTime)
{
	if (!m_movingRight)
	{
		m_playerState.walking = true;
		m_velocity.x -= (m_acceleration * m_speedMultiplier);
		m_animation.setAnimationFaceRight(false);
		m_movingLeft = true;
	}
}

void PlayerCharacter::handleDKeyboardButtonPressed(float deltaTime)
{
	if (!m_movingLeft)
	{
		m_playerState.walking = true;
		m_velocity.x += (m_acceleration * m_speedMultiplier);
		m_animation.setAnimationFaceRight(true);
		m_movingRight = true;
	}
}

void PlayerCharacter::handleSpaceKeyboardButtonPressed(float deltaTime)
{
	if (m_canJump)
	{
		m_playerState.jumping = true;
		m_canJump = false;
		//square root( 2.0f * gravity * jumpHeight)
		m_velocity.y = -sqrtf(2.0f * 981.0f * m_jumpHeight);
	}
}

void PlayerCharacter::handleLShiftKeyboardButtonPressed(float deltaTime)
{
	if (m_playerState.walking && m_canJump && !m_playerState.pushing)
	{
		m_speedMultiplier = 2.0f;
		m_playerState.running = true;
	}
	else if (m_playerState.pushing)
	{
		m_speedMultiplier = 1.0f;
		m_playerState.running = false;
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
	m_velocity.x = 0.0f; //insta stop moving when key isnt pressed
	//velocity.x *= 0.0f; //slowly stop moving (higher number=slower stop time, lower number=faster stop time)
	m_playerState.walking = false;
	m_playerState.running = false;
	m_movingLeft = false;
}

void PlayerCharacter::handleDKeyboardButtonReleased(float deltaTime)
{
	m_velocity.x = 0.0f;
	m_playerState.walking = false;
	m_playerState.running = false;
	m_movingRight = false;
}

void PlayerCharacter::handleSpaceKeyboardButtonReleased(float deltaTime)
{

}

void PlayerCharacter::handleLShiftKeyboardButtonReleased(float deltaTime)
{
	m_speedMultiplier = 1.0f;
	m_playerState.running = false;
}