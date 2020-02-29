#pragma once
#include "RenderableObject.h"
#include <vector>
#include "SFML/Graphics.hpp"

static const float VIEW_HEIGHT = 600.0f;
static const float VIEW_WIDTH = 1280.0f;

class Renderer
{
public:
	void renderObjects();
	static Renderer& getInstance();
	sf::RenderWindow& getWindow();
	sf::View& getView();

private:
	Renderer();
	~Renderer();
	Renderer(Renderer const&) {};
	Renderer& operator=(Renderer const&) {};

public:
	std::vector<RenderableObject*> renderableObjects;

private:
	sf::RenderWindow* window;
	sf::View* view;
};

