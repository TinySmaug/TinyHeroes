#pragma once
#include <SFML/Graphics.hpp>

class CollisionObject
{
public:
	CollisionObject(sf::FloatRect& body);
	virtual ~CollisionObject();

	virtual void onCollision(CollisionObject & other, sf::Vector2f& direction, sf::FloatRect& intersectionRect) = 0;

	bool checkCollision(CollisionObject& other, sf::Vector2f& direction, sf::FloatRect& intersectionRect) const;

private:
	sf::FloatRect& body;
};

