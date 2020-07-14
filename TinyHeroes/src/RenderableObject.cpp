#include "RenderableObject.h"
#include "Renderer.h"
#include <algorithm>

RenderableObject::RenderableObject(int renderDepth)
	: m_renderDepth(renderDepth)
{
}


RenderableObject::~RenderableObject()
{
}

void RenderableObject::setRenderDepth(int depth)
{
	m_renderDepth = depth;
	std::stable_sort(Renderer::getInstance().getRenderableObjects().begin(), Renderer::getInstance().getRenderableObjects().end(),
		[](auto objA, auto objB) { return objA->getRenderDepth() < objB->getRenderDepth(); });
}


