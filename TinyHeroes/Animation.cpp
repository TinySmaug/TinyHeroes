#include "Animation.h"

Animation::Animation()
{
	totalTime = 0.0f;
	currentImage = 0;
}

Animation::~Animation()
{
}

void Animation::update(float deltaTime)
{
	uvRect.width = animationTextures[info.animationIndex].getSize().x / static_cast<float>(info.imageCount);
	uvRect.height = animationTextures[info.animationIndex].getSize().y;
	totalTime += deltaTime;

	if (currentImage >= info.imageCount)
	{
		currentImage = 0;
	}

	if (totalTime >= info.switchTime)
	{
		totalTime -= info.switchTime;
		currentImage++;

		if (currentImage >= info.imageCount)
		{
			currentImage = 0;
		}
	}

	uvRect.top = 0;

	if (info.faceRight)
	{
		uvRect.left = currentImage * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
