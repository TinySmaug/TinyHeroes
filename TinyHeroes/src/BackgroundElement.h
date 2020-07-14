#pragma once

#include "RenderableObject.h"

class BackgroundElement 

{
public:
	BackgroundElement(std::string file);
	~BackgroundElement();

	void render();
	void update(float velocity, float deltaTime);
	void checkBounds(float velocity, float deltaTime);

	
private:
	sf::Texture m_layerTexture;
	sf::Sprite m_backgroundLayer;
};

