#pragma once
#include <SFML/Graphics.hpp>

class CollisionObject
{
public:
	CollisionObject(sf::FloatRect& body);
	virtual ~CollisionObject();

	virtual void onCollision(CollisionObject & other) = 0;
	virtual void onCollisionEnd(CollisionObject & other) = 0;

	bool checkCollision(CollisionObject& other);
	bool isMovable() { return m_movable; };

protected:
	sf::FloatRect m_intersectionRect;
	bool m_movable;

private:
	sf::FloatRect& m_body;
};

