#include "SelectIcon.h"
#include "Renderer.h"


SelectIcon::SelectIcon(std::string file)
	:RenderableObject(1)
{
	m_texture.loadFromFile(file);
	m_icon.setTexture(m_texture);

	m_body.width = static_cast<float>(m_texture.getSize().x);
	m_body.height = static_cast<float>(m_texture.getSize().y);
}

SelectIcon::~SelectIcon()
{
}

void SelectIcon::render()
{
	if (!m_hidden)
	{
		Renderer::getInstance().getWindow().draw(m_icon);
	}
}

void SelectIcon::setPosition(float xPos, float yPos)
{
	m_icon.setPosition(xPos, yPos);
	m_body.left = m_icon.getPosition().x;
	m_body.top = m_icon.getPosition().y;
}

void SelectIcon::setScale(float xScale, float yScale)
{
	m_icon.setScale(xScale, yScale);
	m_body.width *= xScale;
	m_body.height *= yScale;
}