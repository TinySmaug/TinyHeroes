#include "Entity.h"



Entity::Entity(std::string texturePath)
{
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
}


Entity::~Entity()
{
}

void Entity::render(sf::RenderWindow & window)
{
	window.draw(sprite);
}

void Entity::resize(sf::RenderWindow & window)
{
	
}

