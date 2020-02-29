#include "Animation.h"

Animation::Animation()
{
	totalTime = 0.0f;
	info.currentImage = 0;
}

Animation::~Animation()
{
}

void Animation::update(float deltaTime)
{
	if (info.currentImage >= info.imageCount)
	{
		info.currentImage = 0;
	}

	uvRect.width = animationTextures[info.animationIndex].getSize().x / static_cast<float>(info.imageCount);
	uvRect.height = animationTextures[info.animationIndex].getSize().y;
	totalTime += deltaTime;

	if (totalTime >= info.switchTime)
	{
		totalTime -= info.switchTime;
		info.currentImage++;

		if (info.currentImage >= info.imageCount)
		{
			info.currentImage = 0;
		}
	}

	uvRect.top = 0;

	if (info.faceRight)
	{
		uvRect.left = info.currentImage * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (info.currentImage + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
