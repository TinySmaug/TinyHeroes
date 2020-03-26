#include "SelectionScreen.h"
#include "Renderer.h"
#include "Background.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Platform.h"


SelectionScreen::SelectionScreen()
{
	heroSelectionComplete = false;
	backgroundSelectionComplete = false;

	backgroundTexture.loadFromFile("StartingScreen/StartingScreenBackground.png");
	sf::Vector2u bgTextureSize = backgroundTexture.getSize();
	sf::Vector2f bgTextureScale(static_cast<float>(Renderer::getInstance().getView().getSize().x) / bgTextureSize.x,
		static_cast<float>(Renderer::getInstance().getView().getSize().y) / bgTextureSize.y);
	background.setTexture(backgroundTexture);
	background.setScale(bgTextureScale);

	font.loadFromFile("StartingScreen/Planes_ValMore.ttf");

	//Hero Selection Screen
	chooseHeroText.setFont(font);
	chooseHeroText.setString("Choose your hero: ");
	chooseHeroText.setCharacterSize(56);
	chooseHeroText.setFillColor(sf::Color::White);
	chooseHeroText.setOutlineColor(sf::Color::Black);
	chooseHeroText.setOutlineThickness(3.0f);
	chooseHeroText.setPosition(Renderer::getInstance().getView().getSize().x / 3.3f,
		Renderer::getInstance().getView().getSize().y / 11.5f);

	PinkMonster = new SelectIcon("StartingScreen/PinkMonsterPortrait.png");
	PinkMonster->setPosition(Renderer::getInstance().getView().getSize().x / 4.0f,
		Renderer::getInstance().getView().getSize().y / 3.0f);
	PinkMonster->setScale(3.5f, 3.5f);
	OwletMonster = new SelectIcon("StartingScreen/OwletMonsterPortrait.png");
	OwletMonster->setPosition(Renderer::getInstance().getView().getSize().x / 2.2f,
		Renderer::getInstance().getView().getSize().y / 3.0f);
	OwletMonster->setScale(3.5f, 3.5f);
	DudeMonster = new SelectIcon("StartingScreen/DudeMonsterPortrait.png");
	DudeMonster->setPosition(Renderer::getInstance().getView().getSize().x / 1.5f,
		Renderer::getInstance().getView().getSize().y / 3.0f);
	DudeMonster->setScale(3.5f, 3.5f);

	//Background Selection Screen
	chooseBackgroundText.setFont(font);
	chooseBackgroundText.setString("Choose a background: ");
	chooseBackgroundText.setCharacterSize(56);
	chooseBackgroundText.setFillColor(sf::Color::White);
	chooseBackgroundText.setOutlineColor(sf::Color::Black);
	chooseBackgroundText.setOutlineThickness(3.0f);
	chooseBackgroundText.setPosition(Renderer::getInstance().getView().getSize().x / 3.3f,
		Renderer::getInstance().getView().getSize().y / 11.5f);

	Forest = new SelectIcon("StartingScreen/Forest.png");
	Forest->setPosition(Renderer::getInstance().getView().getSize().x / 4.5f,
		Renderer::getInstance().getView().getSize().y / 4.0f);
	Forest->setScale(0.7f, 0.7f);

	Mountain = new SelectIcon("StartingScreen/Mountain.png");
	Mountain->setPosition(Renderer::getInstance().getView().getSize().x / 1.9f,
		Renderer::getInstance().getView().getSize().y / 4.0f);
	Mountain->setScale(0.7f, 0.7f);

	Desert = new SelectIcon("StartingScreen/Desert.png");
	Desert->setPosition(Renderer::getInstance().getView().getSize().x / 4.5f,
		Renderer::getInstance().getView().getSize().y / 1.7f);
	Desert->setScale(0.7f, 0.7f);

	Waterfall = new SelectIcon("StartingScreen/Waterfall.png");
	Waterfall->setPosition(Renderer::getInstance().getView().getSize().x / 1.9f,
		Renderer::getInstance().getView().getSize().y / 1.7f);
	Waterfall->setScale(0.7f, 0.7f);

	InputManager::InputHandlerData tmp;
	tmp.ActivationHandler = std::bind(&SelectionScreen::handleLeftMouseButtonClick, this, std::placeholders::_1);
	tmp.DeactivationHandler = std::bind(&SelectionScreen::handleLeftMouseButtonReleased, this, std::placeholders::_1);
	InputManager::getInstance().addMouseInputHandler(sf::Mouse::Button::Left, tmp);
}

SelectionScreen::~SelectionScreen()
{
}

void SelectionScreen::destroyIcons()
{
	delete PinkMonster;
	delete OwletMonster;
	delete DudeMonster;

	delete Forest;
	delete Mountain;
	delete Desert;
	delete Waterfall;
}

void SelectionScreen::render()
{
	Renderer::getInstance().getWindow().draw(background);
	if (!heroSelectionComplete)
	{
		Renderer::getInstance().getWindow().draw(chooseHeroText);
		PinkMonster->render();
		OwletMonster->render();
		DudeMonster->render();
	}
	else if (!backgroundSelectionComplete)
	{
		Renderer::getInstance().getWindow().draw(chooseBackgroundText);
		Forest->render();
		Mountain->render();
		Desert->render();
		Waterfall->render();
	}
}

void SelectionScreen::handleLeftMouseButtonClick(float deltaTime)
{
}

void SelectionScreen::handleLeftMouseButtonReleased(float deltaTime)
{
	sf::Vector2i mousePixelPosition = sf::Mouse::getPosition(Renderer::getInstance().getWindow());
	sf::Vector2f worldPos = Renderer::getInstance().getWindow().mapPixelToCoords(mousePixelPosition);
	if (!heroSelectionComplete)
	{
		makeBackgroundsHiddenFromClickDetection();
		makeHeroesVisibleToClickDetection();
		chosenHeroFilePath = std::string("Heroes/");

		if (PinkMonster->containsPoint(worldPos))
		{
			chosenHeroFilePath.append("PinkMonster/Pink_Monster.png");
			heroSelectionComplete = true;
		}
		else if (OwletMonster->containsPoint(worldPos))
		{
			chosenHeroFilePath.append("OwletMonster/Owlet_Monster.png");
			heroSelectionComplete = true;
		}
		else if (DudeMonster->containsPoint(worldPos))
		{
			chosenHeroFilePath.append("DudeMonster/Dude_Monster.png");
			heroSelectionComplete = true;
		}
		if (heroSelectionComplete)
		{
			makeHeroesHiddenFromClickDetection();
			makeBackgroundsVisibleToClickDetection();
		}
	}
	else if (!backgroundSelectionComplete)
	{
		int layerNumber;
		std::string chosenBackgroundFilePath("Backgrounds/");
		std::string platformTilePath("World/");

		if (Forest->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Forest");
			platformTilePath.append("ForestPlatformTile.png");
			layerNumber = 7;
			backgroundSelectionComplete = true;
		}
		else if (Mountain->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Mountain");
			platformTilePath.append("MountainPlatformTile.png");
			layerNumber = 7;
			backgroundSelectionComplete = true;
		}
		else if (Desert->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Desert");
			platformTilePath.append("DesertPlatformTile.png");
			layerNumber = 9;
			backgroundSelectionComplete = true;
		}
		else if (Waterfall->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Waterfall");
			platformTilePath.append("WaterfallPlatformTile.png");
			layerNumber = 5;
			backgroundSelectionComplete = true;
		}
		if (backgroundSelectionComplete)
		{
			Background* background = new Background(chosenBackgroundFilePath, layerNumber, -1);
			Platform* platform1 = new Platform(platformTilePath, 2);
			platform1->setPosition(sf::Vector2f(-300.0f, 560.0f));
			platform1->setSize(1280, 100);
			Platform* platform2 = new Platform(platformTilePath, 2);
			platform2->setPosition(sf::Vector2f(-300.0f + 1280.0f + 150.0f, 560.0f));
			platform2->setSize(1280, 100);
		}
	}
}

void SelectionScreen::removeInputHandlerFunctions()
{
	InputManager::getInstance().removeMouseInputHandler(sf::Mouse::Button::Left);
}

void SelectionScreen::makeHeroesHiddenFromClickDetection()
{
	PinkMonster->setHidden(true);
	OwletMonster->setHidden(true);
	DudeMonster->setHidden(true);
}

void SelectionScreen::makeBackgroundsHiddenFromClickDetection()
{
	Forest->setHidden(true);
	Mountain->setHidden(true);
	Waterfall->setHidden(true);
	Desert->setHidden(true);
}

void SelectionScreen::makeHeroesVisibleToClickDetection()
{
	PinkMonster->setHidden(false);
	OwletMonster->setHidden(false);
	DudeMonster->setHidden(false);
}

void SelectionScreen::makeBackgroundsVisibleToClickDetection()
{
	Forest->setHidden(false);
	Mountain->setHidden(false);
	Waterfall->setHidden(false);
	Desert->setHidden(false);
}
