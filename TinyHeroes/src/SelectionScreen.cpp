#include "SelectionScreen.h"
#include "Renderer.h"
#include "Background.h"
#include "InputManager.h"
#include "Platform.h"


SelectionScreen::SelectionScreen()
{
	heroSelectionComplete = false;
	backgroundSelectionComplete = false;

	m_backgroundTexture.loadFromFile("StartingScreen/StartingScreenBackground.png");
	sf::Vector2u bgTextureSize = m_backgroundTexture.getSize();
	sf::Vector2f bgTextureScale(static_cast<float>(Renderer::getInstance().getView().getSize().x) / bgTextureSize.x,
		static_cast<float>(Renderer::getInstance().getView().getSize().y) / bgTextureSize.y);
	m_background.setTexture(m_backgroundTexture);
	m_background.setScale(bgTextureScale);

	m_font.loadFromFile("StartingScreen/Planes_ValMore.ttf");

	//Hero Selection Screen
	m_chooseHeroText.setFont(m_font);
	m_chooseHeroText.setString("Choose your hero: ");
	m_chooseHeroText.setCharacterSize(56);
	m_chooseHeroText.setFillColor(sf::Color::White);
	m_chooseHeroText.setOutlineColor(sf::Color::Black);
	m_chooseHeroText.setOutlineThickness(3.0f);
	m_chooseHeroText.setPosition(Renderer::getInstance().getView().getSize().x / 3.3f,
		Renderer::getInstance().getView().getSize().y / 11.5f);

	m_pinkMonster = new SelectIcon("StartingScreen/PinkMonsterPortrait.png");
	m_pinkMonster->setPosition(Renderer::getInstance().getView().getSize().x / 4.0f,
		Renderer::getInstance().getView().getSize().y / 3.0f);
	m_pinkMonster->setScale(3.5f, 3.5f);
	m_owletMonster = new SelectIcon("StartingScreen/OwletMonsterPortrait.png");
	m_owletMonster->setPosition(Renderer::getInstance().getView().getSize().x / 2.2f,
		Renderer::getInstance().getView().getSize().y / 3.0f);
	m_owletMonster->setScale(3.5f, 3.5f);
	m_dudeMonster = new SelectIcon("StartingScreen/DudeMonsterPortrait.png");
	m_dudeMonster->setPosition(Renderer::getInstance().getView().getSize().x / 1.5f,
		Renderer::getInstance().getView().getSize().y / 3.0f);
	m_dudeMonster->setScale(3.5f, 3.5f);

	//Background Selection Screen
	m_chooseBackgroundText.setFont(m_font);
	m_chooseBackgroundText.setString("Choose a background: ");
	m_chooseBackgroundText.setCharacterSize(56);
	m_chooseBackgroundText.setFillColor(sf::Color::White);
	m_chooseBackgroundText.setOutlineColor(sf::Color::Black);
	m_chooseBackgroundText.setOutlineThickness(3.0f);
	m_chooseBackgroundText.setPosition(Renderer::getInstance().getView().getSize().x / 3.3f,
		Renderer::getInstance().getView().getSize().y / 11.5f);

	m_forest = new SelectIcon("StartingScreen/Forest.png");
	m_forest->setPosition(Renderer::getInstance().getView().getSize().x / 4.5f,
		Renderer::getInstance().getView().getSize().y / 4.0f);
	m_forest->setScale(0.7f, 0.7f);

	m_mountain = new SelectIcon("StartingScreen/Mountain.png");
	m_mountain->setPosition(Renderer::getInstance().getView().getSize().x / 1.9f,
		Renderer::getInstance().getView().getSize().y / 4.0f);
	m_mountain->setScale(0.7f, 0.7f);

	m_desert = new SelectIcon("StartingScreen/Desert.png");
	m_desert->setPosition(Renderer::getInstance().getView().getSize().x / 4.5f,
		Renderer::getInstance().getView().getSize().y / 1.7f);
	m_desert->setScale(0.7f, 0.7f);

	m_waterfall = new SelectIcon("StartingScreen/Waterfall.png");
	m_waterfall->setPosition(Renderer::getInstance().getView().getSize().x / 1.9f,
		Renderer::getInstance().getView().getSize().y / 1.7f);
	m_waterfall->setScale(0.7f, 0.7f);

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
	delete m_pinkMonster;
	delete m_owletMonster;
	delete m_dudeMonster;

	delete m_forest;
	delete m_mountain;
	delete m_desert;
	delete m_waterfall;
}

void SelectionScreen::render()
{
	Renderer::getInstance().getWindow().draw(m_background);
	if (!heroSelectionComplete)
	{
		Renderer::getInstance().getWindow().draw(m_chooseHeroText);
		m_pinkMonster->render();
		m_owletMonster->render();
		m_dudeMonster->render();
	}
	else if (!backgroundSelectionComplete)
	{
		Renderer::getInstance().getWindow().draw(m_chooseBackgroundText);
		m_forest->render();
		m_mountain->render();
		m_desert->render();
		m_waterfall->render();
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
		m_chosenHeroFilePath = std::string("Heroes/");

		if (m_pinkMonster->containsPoint(worldPos))
		{
			m_chosenHeroFilePath.append("PinkMonster/Pink_Monster.png");
			heroSelectionComplete = true;
		}
		else if (m_owletMonster->containsPoint(worldPos))
		{
			m_chosenHeroFilePath.append("OwletMonster/Owlet_Monster.png");
			heroSelectionComplete = true;
		}
		else if (m_dudeMonster->containsPoint(worldPos))
		{
			m_chosenHeroFilePath.append("DudeMonster/Dude_Monster.png");
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

		if (m_forest->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Forest");
			platformTilePath.append("ForestPlatformTile.png");
			layerNumber = 7;
			backgroundSelectionComplete = true;
		}
		else if (m_mountain->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Mountain");
			platformTilePath.append("MountainPlatformTile.png");
			layerNumber = 7;
			backgroundSelectionComplete = true;
		}
		else if (m_desert->containsPoint(worldPos))
		{
			chosenBackgroundFilePath.append("Desert");
			platformTilePath.append("DesertPlatformTile.png");
			layerNumber = 9;
			backgroundSelectionComplete = true;
		}
		else if (m_waterfall->containsPoint(worldPos))
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
	m_pinkMonster->setHidden(true);
	m_owletMonster->setHidden(true);
	m_dudeMonster->setHidden(true);
}

void SelectionScreen::makeBackgroundsHiddenFromClickDetection()
{
	m_forest->setHidden(true);
	m_mountain->setHidden(true);
	m_waterfall->setHidden(true);
	m_desert->setHidden(true);
}

void SelectionScreen::makeHeroesVisibleToClickDetection()
{
	m_pinkMonster->setHidden(false);
	m_owletMonster->setHidden(false);
	m_dudeMonster->setHidden(false);
}

void SelectionScreen::makeBackgroundsVisibleToClickDetection()
{
	m_forest->setHidden(false);
	m_mountain->setHidden(false);
	m_waterfall->setHidden(false);
	m_desert->setHidden(false);
}
