#pragma once
#include "SFML\Graphics.hpp"

class RenderableObject
{
public:
	RenderableObject(int renderDepth);
	virtual ~RenderableObject();

	virtual void render() = 0;

	int getRenderDepth() const { return renderDepth; };

protected:
	int renderDepth;
};

