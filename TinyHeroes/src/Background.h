#pragma once
#include "BackgroundElement.h"
#include <vector>

class Background : public RenderableObject
{
public:
	Background(std::string file, int layerNum, int depth);
	~Background();

	void render();
	sf::FloatRect getRenderableArea();
	//void setTexture(std::string file, int layerNum);

	void update(float deltaTime);

public:
	std::vector<BackgroundElement*> background;
};

