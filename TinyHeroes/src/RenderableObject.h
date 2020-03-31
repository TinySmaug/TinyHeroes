#pragma once
#include "SFML\Graphics.hpp"

class RenderableObject
{
public:
	RenderableObject(int renderDepth);
	virtual ~RenderableObject();

	virtual void render() = 0;
	virtual sf::FloatRect getRenderableArea() = 0;
	int getRenderDepth() const { return renderDepth; };
	void setHidden(bool hidden) { this->hidden = hidden; };
	bool isHidden() { return hidden; };

protected:
	void setRenderDepth(int depth);

protected:
	int renderDepth;
	bool hidden = false;
};

