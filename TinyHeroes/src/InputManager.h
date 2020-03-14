#pragma once
#include <map>
#include <functional>
#include "SFML/Graphics.hpp"

class InputManager
{
public:
	static InputManager& getInstance();
	void update(float deltaTime);

	typedef struct InputHandlerData
	{
		std::function<void(float deltaTime)> ActivationHandler;
		std::function<void(float deltaTime)> DeactivationHandler;
		bool wasActiveInPreviousFrame = false;
	} InputHandlerData;

	std::map<sf::Keyboard::Key, InputHandlerData >& getKeyboardEventHandlers() { return keyboardInputHandlers; };
	std::map<sf::Mouse::Button, InputHandlerData >& getMouseEventHandlers() { return mouseInputHandlers; };

	bool addKeyboardInputHandler(sf::Keyboard::Key, InputHandlerData);
	bool addMouseInputHandler(sf::Mouse::Button, InputHandlerData);

	bool removeKeyboardInputHandler(sf::Keyboard::Key);
	bool removeMouseInputHandler(sf::Mouse::Button);

private:
	InputManager();
	~InputManager();
	InputManager(InputManager const&) {};
	InputManager& operator=(InputManager const&) {};

private:
	std::map<sf::Keyboard::Key, InputHandlerData> keyboardInputHandlers;
	std::map<sf::Mouse::Button, InputHandlerData> mouseInputHandlers;
};

