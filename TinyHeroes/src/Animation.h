#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>

class Animation
{
public:
	Animation();
	~Animation();

	typedef struct animationInfo {
		sf::Texture animationTexture;
		std::string animationName;
		unsigned int imageCount;
		float totalAnimationTime;
		float frameSwitchTime;
		sf::IntRect frameRect;
	} animationInfo;

	void update(float deltaTime);
	void setAnimations(std::string txtFilePath);
	void setSprite(sf::Sprite& sprite) { this->sprite = &sprite; };

	void setCurrentAnimationAs(std::string animationName);
	void setAnimationFaceRight(bool right);
	bool isAnimationFacingRight() { return faceRight; };

public:
	unsigned int currentImage;
	std::vector<animationInfo> animations;

private:
	animationInfo& currentAnimation();

private:
	bool faceRight = true;
	bool previousFaceRight = true;
	float currentFrameTime;
	std::string currentAnimationName;
	std::string previousAnimationName;
	std::ifstream animationsFile;
	sf::Sprite* sprite;
};

