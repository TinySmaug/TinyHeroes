#pragma once
#include <SFML/Graphics.hpp>

class CollisionObject
{
public:
	CollisionObject(sf::FloatRect& body);
	virtual ~CollisionObject();

	virtual void onCollision(CollisionObject & other) = 0;

	bool checkCollision(CollisionObject& other);

protected:
	sf::FloatRect intersectionRect;

private:
	sf::FloatRect& body;
};

