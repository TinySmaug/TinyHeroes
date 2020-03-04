#include "Animation.h"

Animation::Animation()
{
	totalTime = 0.0f;
	currentAnimationInfo.currentImage = 0;
}

Animation::~Animation()
{
}

void Animation::update(float deltaTime)
{
	if (currentAnimationInfo.currentImage >= currentAnimationInfo.imageCount)
	{
		currentAnimationInfo.currentImage = 0;
	}

	uvRect.width = animationTextures[currentAnimationInfo.animationIndex].getSize().x / static_cast<float>(currentAnimationInfo.imageCount);
	uvRect.height = animationTextures[currentAnimationInfo.animationIndex].getSize().y;
	totalTime += deltaTime;

	if (totalTime >= currentAnimationInfo.switchTime)
	{
		totalTime -= currentAnimationInfo.switchTime;
		currentAnimationInfo.currentImage++;

		if (currentAnimationInfo.currentImage >= currentAnimationInfo.imageCount)
		{
			currentAnimationInfo.currentImage = 0;
		}
	}

	uvRect.top = 0;

	if (currentAnimationInfo.faceRight)
	{
		uvRect.left = currentAnimationInfo.currentImage * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentAnimationInfo.currentImage + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
