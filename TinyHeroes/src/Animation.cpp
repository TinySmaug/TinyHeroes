#include "Animation.h"
#include <cassert>

#define DEBUG 0

Animation::Animation()
{
	m_currentFrameTime = 0.0f;
	m_currentImage = 0;
	m_currentAnimationName = std::string("idle");
}

Animation::~Animation()
{
}

void Animation::setAnimations(std::string txtFilePath)
{
	m_animationsFile.open(txtFilePath.c_str());
	if (!m_animationsFile.is_open())
	{
		return;
	}
	auto slashPosition = txtFilePath.find_last_of('/');
	std::string folderPath = txtFilePath.substr(0, slashPosition + 1);
	std::string line;
	while (std::getline(m_animationsFile, line))
	{
		animationInfo animation;

		auto textureEndPosition = line.find_first_of(' ');
		std::string texturePath = folderPath + line.substr(0, textureEndPosition);
		animation.animationTexture.loadFromFile(texturePath);
		
		auto imageCountEndPosition = line.find_first_of(' ', textureEndPosition+1);
		std::string imageCountString = line.substr(textureEndPosition+1, imageCountEndPosition -textureEndPosition-1);
		animation.imageCount = std::stoi(imageCountString);

		auto animationNameEndPosition = line.find_first_of(' ', imageCountEndPosition+1);
		animation.animationName = line.substr(imageCountEndPosition+1, animationNameEndPosition-imageCountEndPosition-1);

		auto totalAnimationTimeEndPosition = line.find_first_of(' ', animationNameEndPosition+1);
		std::string totalAnimationTimeString = line.substr(animationNameEndPosition+1, 
			totalAnimationTimeEndPosition-animationNameEndPosition-1);
		animation.totalAnimationTime = std::stof(totalAnimationTimeString);

		animation.frameSwitchTime = animation.totalAnimationTime / static_cast<float>(animation.imageCount);

		animation.frameRect.top = 0;
		animation.frameRect.width = animation.animationTexture.getSize().x / static_cast<float>(animation.imageCount);
		animation.frameRect.height = animation.animationTexture.getSize().y;

		m_animations.emplace_back(animation);
	}	
}

void Animation::setCurrentAnimationAs(std::string animationName)
{
	m_previousAnimationName = m_currentAnimationName;
	m_currentAnimationName = animationName;
}

void Animation::setAnimationFaceRight(bool right)
{
	m_previousFaceRight = m_faceRight;
	m_faceRight = right;
}

Animation::animationInfo& Animation::currentAnimation()
{
	std::string animationName = m_currentAnimationName;
	auto position = std::find_if(m_animations.begin(), m_animations.end(),
		[&](animationInfo animation) { return animation.animationName == animationName; });
	if (DEBUG)
	{
		assert(position != m_animations.end());
	}
	return *position;
}


void Animation::update(float deltaTime)
{
	animationInfo& currentAnimationVar = currentAnimation();

	if (m_currentAnimationName != m_previousAnimationName || m_faceRight != m_previousFaceRight)
	{
		m_currentImage = 0;
		m_currentFrameTime = 0.0f;
	}

	m_currentFrameTime += deltaTime;

	if (m_currentFrameTime >= currentAnimationVar.frameSwitchTime)
	{
		m_currentFrameTime -= currentAnimationVar.frameSwitchTime;
		m_currentImage++;

		if (m_currentImage >= currentAnimationVar.imageCount)
		{
			m_currentImage = 0;
		}
	}

	if (m_faceRight)
	{
		currentAnimationVar.frameRect.left = m_currentImage * currentAnimationVar.frameRect.width;
		currentAnimationVar.frameRect.width = abs(currentAnimationVar.frameRect.width);
	}
	else
	{
		currentAnimationVar.frameRect.left = (m_currentImage + 1) * abs(currentAnimationVar.frameRect.width);
		currentAnimationVar.frameRect.width = -abs(currentAnimationVar.frameRect.width);
	}

	m_sprite->setTextureRect(currentAnimationVar.frameRect);
	m_sprite->setTexture(currentAnimationVar.animationTexture);
}