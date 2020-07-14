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

	std::vector<RenderableObject*>& getRenderableObjects() { return m_renderableObjects; };
	void addRenderableObject(RenderableObject* object);
	std::vector<RenderableObject*>::iterator removeRenderableObject(std::vector<RenderableObject*>::iterator i);

private:
	Renderer();
	~Renderer();
	Renderer(Renderer const&) {};
	Renderer& operator=(Renderer const&) {};

	bool outOfView(RenderableObject& object) const;

private:
	std::vector<RenderableObject*> m_renderableObjects;
	sf::RenderWindow* m_window;
	sf::View* m_view;
};

