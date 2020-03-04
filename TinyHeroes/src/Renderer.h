#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class RenderableObject;

class Renderer
{
public:
	void renderObjects();
	static Renderer& getInstance();
	sf::RenderWindow& getWindow() const;
	sf::View& getView() const;

	std::vector<RenderableObject*>& getRenderableObjects() { return renderableObjects; };
	void addRenderableObject(RenderableObject* object);
	std::vector<RenderableObject*>::iterator removeRenderableObject(std::vector<RenderableObject*>::iterator i);

private:
	Renderer();
	~Renderer();
	Renderer(Renderer const&) {};
	Renderer& operator=(Renderer const&) {};

	bool outOfView(RenderableObject& object) const;

private:
	std::vector<RenderableObject*> renderableObjects;
	sf::RenderWindow* window;
	sf::View* view;
};

