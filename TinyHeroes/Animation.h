#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(float switchTime);
	~Animation();

	void update(unsigned int animationRow, unsigned int imageCount, float deltaTime, bool faceRight);

public:
	sf::IntRect uvRect;
	std::vector<sf::Texture> animationTextures;

private:
	unsigned int currentImage;

	float totalTime;
	float switchTime;
};

