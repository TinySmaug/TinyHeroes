#include "RenderableObject.h"
#include "Renderer.h"
#include <algorithm>

RenderableObject::RenderableObject(int renderDepth)
	: renderDepth(renderDepth)
{
}


RenderableObject::~RenderableObject()
{
}

void RenderableObject::setRenderDepth(int depth)
{
	renderDepth = depth;
	std::stable_sort(Renderer::getInstance().getRenderableObjects().begin(), Renderer::getInstance().getRenderableObjects().end(),
		[](auto objA, auto objB) { return objA->getRenderDepth() < objB->getRenderDepth(); });
}


