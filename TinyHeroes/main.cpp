#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "src\BackgroundElement.h"
#include "src\PlayerCharacter.h"
#include "src\Renderer.h"
#include "src\Background.h"
#include "src\WorldElement.h"
#include "src\WorldInstance.h"

int main()
{
	Renderer& renderer = Renderer::getInstance();
	WorldInstance world;
	
	Background background("Backgrounds/Forest", 7, renderer, -1);

	PlayerCharacter player("Heroes/PinkMonster/Pink_Monster.png", renderer, world, 0);

	WorldElement platform1 = WorldElement("World/Platform.png", renderer, world, 2);
	platform1.setPosition(sf::Vector2f(-300.0f, 560.0f));
	WorldElement platform2("World/Platform.png", renderer, world, 2);
	platform2.setPosition(sf::Vector2f(-300.0f + 1280.0f + 150.0f, 560.0f));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (renderer.getWindow().isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) //20fps minimum always
			deltaTime = 1.0f / 20.0f;

		sf::Event e;
		while (renderer.getWindow().pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				renderer.getWindow().close();
				break;
			/*
			case sf::Event::Resized:
				renderer->resize();
				break;
			*/
			/*
			case sf::Event::TextEntered:
				if(evnt.text.unicode < 128)
					printf("%c", e.text.unicode);
			*/
			}
		}
		renderer.getWindow().clear();
		
		world.updateObjects(deltaTime);

		sf::Vector2f direction;
		sf::FloatRect intersectionRect;
		if (platform1.checkCollision(player, direction, intersectionRect))
			player.onCollision(platform1, direction, intersectionRect);
		if (platform2.checkCollision(player, direction, intersectionRect))
			player.onCollision(platform2, direction, intersectionRect);

		renderer.getView().setCenter(player.getPosition().x + 340.0f, 300.0f);
		renderer.getWindow().setView(renderer.getView());

		background.update(player.getVelocity(), deltaTime, renderer);
	
		renderer.renderObjects();
		renderer.getWindow().display();
	}

	return 0;
}