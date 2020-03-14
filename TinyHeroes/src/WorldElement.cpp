#include "WorldElement.h"
#include "Renderer.h"

WorldElement::WorldElement(std::string texturePath, int depth)
	: Entity(texturePath, depth)
{
	movable = true;
}

WorldElement::~WorldElement()
{
}

void WorldElement::render()
{
	Renderer::getInstance().getWindow().draw(sprite);
}

void WorldElement::onCollision(CollisionObject & other)
{
	if (intersectionRect.width < 0.0f)
	{
		//collision on the left
		move(intersectionRect.width, 0.0f);
	}
	else if (intersectionRect.width > 0.0f)
	{
		//collision on the right
		move(intersectionRect.width, 0.0f);
	}
	if (intersectionRect.height < 0.0f)
	{
		//collision on the bottom
		move(0.0f, intersectionRect.height);
		velocity.y = 0.0f;
	}
}

void WorldElement::update(float deltaTime)
{
	velocity.x = 0.0f;
	velocity.y += WorldInstance::getInstance().getGravity() * deltaTime;
	move(velocity * deltaTime);
}


