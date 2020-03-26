#pragma once
#include "SelectIcon.h"

class Background;

class SelectionScreen
{
public:
	SelectionScreen();
	~SelectionScreen();
	
	void render();
	
	void removeInputHandlerFunctions();
	std::string getChosenHeroFilePath() { return chosenHeroFilePath; };

	void destroyIcons();

public:
	bool heroSelectionComplete;
	bool backgroundSelectionComplete;

private:
	void handleLeftMouseButtonClick(float deltaTime);
	void handleLeftMouseButtonReleased(float deltaTime);

	void makeHeroesHiddenFromClickDetection();
	void makeBackgroundsHiddenFromClickDetection();
	void makeHeroesVisibleToClickDetection();
	void makeBackgroundsVisibleToClickDetection();

private:
	SelectIcon* PinkMonster;
	SelectIcon* OwletMonster;
	SelectIcon* DudeMonster;
	std::string chosenHeroFilePath;

	SelectIcon* Forest;
	SelectIcon* Mountain;
	SelectIcon* Desert;
	SelectIcon* Waterfall;

	sf::Sprite background;
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::Text chooseHeroText;
	sf::Text chooseBackgroundText;
};

