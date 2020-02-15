#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation();
	~Animation();

	void update(float deltaTime);

public:
	sf::IntRect uvRect;
	std::vector<sf::Texture> animationTextures;
	typedef struct animationInfo {
		unsigned int animationIndex;
		unsigned int imageCount;
		bool faceRight;
		float switchTime;
	} animationInfo;
	animationInfo info;

private:
	unsigned int currentImage;
	float totalTime;
};

