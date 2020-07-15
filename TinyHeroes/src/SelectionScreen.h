#pragma once
#include "SelectIcon.h"


class SelectionScreen
{
public:
	SelectionScreen();
	~SelectionScreen();
	
	void render();
	
	void removeInputHandlerFunctions();
	std::string getChosenHeroFilePath() { return m_chosenHeroFilePath; };

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
	SelectIcon* m_pinkMonster;
	SelectIcon* m_owletMonster;
	SelectIcon* m_dudeMonster;
	std::string m_chosenHeroFilePath;

	SelectIcon* m_forest;
	SelectIcon* m_mountain;
	SelectIcon* m_desert;
	SelectIcon* m_waterfall;

	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;
	sf::Font m_font;
	sf::Text m_chooseHeroText;
	sf::Text m_chooseBackgroundText;
};

