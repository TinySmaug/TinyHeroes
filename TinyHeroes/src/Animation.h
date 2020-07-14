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
	void setSprite(sf::Sprite& sprite) { this->m_sprite = &sprite; };

	void setCurrentAnimationAs(std::string animationName);
	void setAnimationFaceRight(bool right);
	bool isAnimationFacingRight() { return m_faceRight; };

public:
	unsigned int m_currentImage;
	std::vector<animationInfo> m_animations;

private:
	animationInfo& currentAnimation();

private:
	bool m_faceRight = true;
	bool m_previousFaceRight = true;
	float m_currentFrameTime;
	std::string m_currentAnimationName;
	std::string m_previousAnimationName;
	std::ifstream m_animationsFile;
	sf::Sprite* m_sprite;
};

