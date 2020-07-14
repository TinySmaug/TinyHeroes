#pragma once
#include "SFML\Graphics.hpp"

class RenderableObject
{
public:
	RenderableObject(int renderDepth);
	virtual ~RenderableObject();

	virtual void render() = 0;
	virtual sf::FloatRect getRenderableArea() = 0;
	int getRenderDepth() const { return m_renderDepth; };
	void setHidden(bool hidden) { this->m_hidden = hidden; };
	bool isHidden() { return m_hidden; };

protected:
	void setRenderDepth(int depth);

protected:
	int m_renderDepth;
	bool m_hidden = false;
};

