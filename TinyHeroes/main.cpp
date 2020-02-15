#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "BackgroundElement.h"
#include "PlayerCharacter.h"
#include "Renderer.h"
#include "Background.h"


int main()
{
	Renderer* renderer = Renderer::getInstance();
	
	Background background("Backgrounds/Forest", 7, renderer->getWindow());
	renderer->renderableObjects.push_back(&background);

	PlayerCharacter player("Heroes/PinkMonster/Pink_Monster.png");
	renderer->renderableObjects.push_back(&player);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (renderer->getWindow().isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) //20fps minimum always
			deltaTime = 1.0f / 20.0f;

		sf::Event e;
		while (renderer->getWindow().pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				renderer->getWindow().close();
				break;
			case sf::Event::Resized:
				renderer->resize();
				break;
			/*
			case sf::Event::TextEntered:
				if(evnt.text.unicode < 128)
					printf("%c", e.text.unicode);
			*/
			}
		}
		renderer->getWindow().clear();
		
		player.update(deltaTime);
		
		renderer->getView().setCenter(player.getPosition().x + 540.0f, 300.0f);
		renderer->getWindow().setView(renderer->getView());

		background.update(player.getVelocity(), deltaTime, renderer->getWindow(), renderer->getView());
	
		renderer->renderObjects();
		renderer->getWindow().display();
	}

	return 0;
}