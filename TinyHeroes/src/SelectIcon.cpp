#include "SelectIcon.h"
#include "Renderer.h"


SelectIcon::SelectIcon(std::string file)
	:RenderableObject(1)
{
	texture.loadFromFile(file);
	icon.setTexture(texture);

	body.width = static_cast<float>(texture.getSize().x);
	body.height = static_cast<float>(texture.getSize().y);
}

SelectIcon::~SelectIcon()
{
}

void SelectIcon::render()
{
	if (!hidden)
	{
		Renderer::getInstance().getWindow().draw(icon);
	}
}

void SelectIcon::setPosition(float xPos, float yPos)
{
	icon.setPosition(xPos, yPos);
	body.left = icon.getPosition().x;
	body.top = icon.getPosition().y;
}

void SelectIcon::setScale(float xScale, float yScale)
{
	icon.setScale(xScale, yScale);
	body.width *= xScale;
	body.height *= yScale;
}