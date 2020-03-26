#include "Animation.h"
#include <cassert>

#define DEBUG 0

Animation::Animation()
{
	currentFrameTime = 0.0f;
	currentImage = 0;
	currentAnimationName = std::string("idle");
}

Animation::~Animation()
{
}

void Animation::setAnimations(std::string txtFilePath)
{
	animationsFile.open(txtFilePath.c_str());
	if (!animationsFile.is_open())
	{
		return;
	}
	auto slashPosition = txtFilePath.find_last_of('/');
	std::string folderPath = txtFilePath.substr(0, slashPosition + 1);
	std::string line;
	while (std::getline(animationsFile, line))
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

		animations.emplace_back(animation);
	}	
}

void Animation::setCurrentAnimationAs(std::string animationName)
{
	previousAnimationName = currentAnimationName;
	currentAnimationName = animationName;
}

void Animation::setAnimationFaceRight(bool right)
{
	previousFaceRight = faceRight;
	faceRight = right;
}

Animation::animationInfo& Animation::currentAnimation()
{
	std::string animationName = currentAnimationName;
	auto position = std::find_if(animations.begin(), animations.end(),
		[&](animationInfo animation) { return animation.animationName == animationName; });
	if (DEBUG)
	{
		assert(position != animations.end());
	}
	return *position;
}


void Animation::update(float deltaTime)
{
	if (currentAnimationName != previousAnimationName || faceRight != previousFaceRight)
	{
		currentImage = 0;
		currentFrameTime = 0.0f;
	}
	
	currentFrameTime += deltaTime;

	if (currentFrameTime >= currentAnimation().frameSwitchTime)
	{
		currentFrameTime -= currentAnimation().frameSwitchTime;
		currentImage++;

		if (currentImage >= currentAnimation().imageCount)
		{
			currentImage = 0;
		}
	}

	if (faceRight)
	{
		currentAnimation().frameRect.left = currentImage * currentAnimation().frameRect.width;
		currentAnimation().frameRect.width = abs(currentAnimation().frameRect.width);
	}
	else
	{
		currentAnimation().frameRect.left = (currentImage + 1) * abs(currentAnimation().frameRect.width);
		currentAnimation().frameRect.width = -abs(currentAnimation().frameRect.width);
	}

	sprite->setTextureRect(currentAnimation().frameRect);
	sprite->setTexture(currentAnimation().animationTexture);
}