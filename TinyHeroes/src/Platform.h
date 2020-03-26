#pragma once
#include "Entity.h"

class Platform : public Entity
{
public:
	Platform(std::string texturePath, int depth);
	~Platform();

	void render() override;
	void onCollision(CollisionObject & other);
	void onCollisionEnd(CollisionObject & other);
	void update(float deltaTime);
	void setSize(int width, int height);
};

