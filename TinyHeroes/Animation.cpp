#include "Animation.h"

Animation::Animation(float switchTime)
{
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage = 0;
}

Animation::~Animation()
{
}

void Animation::update(unsigned int animationRow, unsigned int imageCount, float deltaTime, bool faceRight)
{
	uvRect.width = animationTextures[animationRow].getSize().x / static_cast<float>(imageCount);
	uvRect.height = animationTextures[animationRow].getSize().y;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage++;

		if (currentImage >= imageCount)
		{
			currentImage = 0;
		}
	}

	uvRect.top = 0;

	if (faceRight)
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
