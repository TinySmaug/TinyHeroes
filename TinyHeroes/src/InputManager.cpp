#include "InputManager.h"
#include <cassert>
#define DEBUG 0

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

InputManager& InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::update(float deltaTime)
{
	for (auto i = keyboardInputHandlers.begin(); i != keyboardInputHandlers.end(); i++)
	{
		if (sf::Keyboard::isKeyPressed((*i).first))
		{
			(*i).second.ActivationHandler(deltaTime);
			(*i).second.wasActiveInPreviousFrame = true;
		}
		else if ((*i).second.wasActiveInPreviousFrame)
		{
			(*i).second.DeactivationHandler(deltaTime);
			(*i).second.wasActiveInPreviousFrame = false;
		}
	}
	for (auto i = mouseInputHandlers.begin(); i != mouseInputHandlers.end(); i++)
	{
		if (sf::Mouse::isButtonPressed((*i).first))
		{
			(*i).second.ActivationHandler(deltaTime);
			(*i).second.wasActiveInPreviousFrame = true;
		}
		else if ((*i).second.wasActiveInPreviousFrame)
		{
			(*i).second.DeactivationHandler(deltaTime);
			(*i).second.wasActiveInPreviousFrame = false;
		}
	}
}

bool InputManager::addKeyboardInputHandler(sf::Keyboard::Key key, InputHandlerData data)
{
	bool result = keyboardInputHandlers.try_emplace(key, data).second;
	if (DEBUG)
	{
		assert(result);
	}
	return result;
}

bool InputManager::addMouseInputHandler(sf::Mouse::Button button, InputHandlerData data)
{
	bool result = mouseInputHandlers.try_emplace(button, data).second;
	if (DEBUG)
	{
		assert(result);
	}
	return result;
}

bool InputManager::removeKeyboardInputHandler(sf::Keyboard::Key key)
{
	auto position = keyboardInputHandlers.find(key);
	if (position != keyboardInputHandlers.end())
	{
		keyboardInputHandlers.erase(position);
		return true;
	}
	return false;
}

bool InputManager::removeMouseInputHandler(sf::Mouse::Button button)
{
	auto position = mouseInputHandlers.find(button);
	if (position != mouseInputHandlers.end())
	{
		mouseInputHandlers.erase(position);
		return true;
	}
	return false;
}
