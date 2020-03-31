#include <SFML\Graphics.hpp>
#include <iostream>

#include "src\Renderer.h"
#include "src\WorldInstance.h"
#include "src\CollisionEngine.h"
#include "src\InputManager.h"

#include "src\SelectionScreen.h"

#include "src\PlayerCharacter.h"
#include "src\WorldElement.h"
#include "src\Enemy.h"

#define DEBUG 0

int main()
{
	Renderer& renderer = Renderer::getInstance();
	WorldInstance& world = WorldInstance::getInstance();
	CollisionEngine& collisionEngine = CollisionEngine::getInstance();
	InputManager& inputManager = InputManager::getInstance();

	bool pauseState = false;
	sf::Text pause;
	sf::Font font;
	font.loadFromFile("StartingScreen/Planes_ValMore.ttf");
	pause.setFont(font);
	pause.setString("Pause");
	pause.setCharacterSize(56);
	pause.setOutlineColor(sf::Color::Black);
	pause.setOutlineThickness(3.0f);

	bool selectionComplete = false;
	SelectionScreen selectionScreen;
	selectionScreen.heroSelectionComplete = false;

	sf::Text fps;
	fps.setFont(font);
	fps.setCharacterSize(20);
	fps.setOutlineColor(sf::Color::Black);
	fps.setOutlineThickness(3.0f);

	PlayerCharacter player("", 1);

	WorldElement rock("World/Rock.png", 1);
	rock.setPosition(sf::Vector2f(-300.0f + 1280.0f + 150.0f + 200.0f, 496.0f));
	rock.setScale(sf::Vector2f(4.0f, 4.0f));

	Enemy reaper("Enemies/GreenReaper/Green_Reaper.png", 1);
	reaper.setPosition(reaper.startingPosition);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (renderer.getWindow().isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 5.0f)
			deltaTime = 1.0f / 5.0f;

		sf::Event e;
		while (renderer.getWindow().pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				renderer.getWindow().close();
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::P)
				{
					pauseState = pauseState ? false : true;
				}
			/*
			case sf::Event::Resized:
				break;
			*/
			/*
			case sf::Event::TextEntered:
				if(evnt.text.unicode < 128)
					printf("%c", e.text.unicode);
			*/
			}
		}
		
		if (!selectionComplete && (renderer.getWindow().hasFocus() || DEBUG))
		{
			renderer.getWindow().clear();

			selectionScreen.render();

			renderer.getWindow().display();

			inputManager.update(deltaTime);

			if (selectionScreen.backgroundSelectionComplete == true)
			{
				selectionComplete = true;
				selectionScreen.removeInputHandlerFunctions();

				player.setTexture(selectionScreen.getChosenHeroFilePath());
				player.setPosition(0.0f, 400.0f);
				player.setScale(sf::Vector2f(3.0f, 3.0f));

				selectionScreen.destroyIcons();

				player.addInputHandlerFunctions();
			}
		}
		else if (renderer.getWindow().hasFocus() || DEBUG)
		{
			if (pauseState)
			{
				pause.setPosition(renderer.getView().getCenter().x - 100.0f, renderer.getView().getCenter().y - 100.0f);
				renderer.renderObjects();
				renderer.getWindow().draw(pause);
				renderer.getWindow().display();
				continue;
			}

			renderer.getWindow().clear();

			inputManager.update(deltaTime);

			world.updateObjects(deltaTime);

			collisionEngine.checkCollisions();

			renderer.getView().setCenter(WorldInstance::getInstance().getPlayerPosition().x + 340.0f, 300.0f);
			renderer.getWindow().setView(renderer.getView());

			renderer.renderObjects();

			if (DEBUG)
			{
				fps.setString(std::to_string(1.0f / deltaTime));
				fps.setPosition(WorldInstance::getInstance().getPlayerPosition().x - 270.0f, 0.0f);
				renderer.getWindow().draw(fps);
			}

			renderer.getWindow().display();
		}
	}

	return 0;
}