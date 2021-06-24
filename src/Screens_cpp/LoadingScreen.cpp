//-------------------------- Include section  ----------------------------
#include "Screens_Headers/LodingScreen.h"
#include "Macros.h"
#include "Resources.h"


//----------------------------- Constractor ------------------------------
// Initializes the images and animations of the player and the balls of
// the charge bar.
//------------------------------------------------------------------------
LoadingScreen::LoadingScreen()
	: m_background(LOADING_CIRCLE_RADIUS),
	playerLoading({ WINDOW_WIDTH / 15.f,WINDOW_HEIGHT / 15.f }),
	m_playerAnimation(Resources::instance().
		moveableAnimationsData(Resources::instance().PLAYER_DATA),
		Operation::Right, playerLoading, Resources::instance().
		getMovableObjectTexture(Resources::instance().PLAYER)),
	m_loadingBar(CIRCLES_LOAD_NUM),
	loadingBar({ LOADING_BAR_WIDTH, LOADING_BAR_HEIGHT })
{
	setLoadingBar();

	playerLoading.setOrigin(playerLoading.getSize() / 2.f);

	playerLoading.setPosition(sf::Vector2f
	(WINDOW_WIDTH,WINDOW_HEIGHT) / 2.f);

	m_background.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::LOADING_BACKGROUND));
	m_background.setOrigin(m_background.getRadius(),
		m_background.getRadius());
	m_background.setPosition(sf::Vector2f(WINDOW_WIDTH,
		WINDOW_HEIGHT) / 2.f);
}


//--------------------------- intialScreenSet ----------------------------
// sets the intial music of the loading screen.
// The intial music of the loading screen is silent.
//------------------------------------------------------------------------
void LoadingScreen::intialScreenSet()
{
	Resources::instance().stopMusic();
	loadTime.restart();
	m_loadingBar.clear();
	loadingIndex = 0;
	setLoadingBar();

}


//-------------------------------- draw ----------------------------------
// Draw the loading screen upon the board and plays the loading animation.
//------------------------------------------------------------------------
void LoadingScreen::draw(sf::RenderWindow& window)
{
	setPlayerBackgroundAnimation();
	setLoadingBarAnimation(loadingIndex);
	for (auto i : m_loadingBar) {
		window.draw(i);
	}
	window.draw(m_background);
	window.draw(playerLoading);
}


//------------------------------ screenRun -------------------------------
// Runs the screen of the loading screen.
//------------------------------------------------------------------------
void LoadingScreen::screenRun(sf::RenderWindow& window,
	bool& toSwitchScreen, int& currentScreen)
{
	ScreenBase::screenRun(window, toSwitchScreen, currentScreen);

	if (loadingIndex >= CIRCLES_LOAD_NUM) 
	{
		currentScreen = GAME;
		toSwitchScreen = true;
	}
}


//--------------------- setPlayerBackgroundAnimation ---------------------
// Sets the background animation.
//------------------------------------------------------------------------
void LoadingScreen::setPlayerBackgroundAnimation()
{
	static float timer = 0;
	static bool increaseAlpha = false;

	auto deltaTime = loadTime.restart();

	m_playerAnimation.update(deltaTime);

	if (backgroundAnim.getElapsedTime().asSeconds() > 0.05f)
	{
		m_background.rotate(ROTATION);
		backgroundAnim.restart();
		if (m_background.getFillColor().a <= MINIMUN_BRIGHTNESSS)
			increaseAlpha = true;
		if (m_background.getFillColor().a >= MAXIMUM_BRIGHTNESS)
			increaseAlpha = false;

		if (increaseAlpha) {
			m_background.setFillColor(sf::Color(255, 255, 255,
				m_background.getFillColor().a + 1));
			m_background.setRadius(m_background.getRadius() + 1);
			m_background.setOrigin(m_background.getRadius(),
				m_background.getRadius());
		}
		else
			m_background.setFillColor(sf::Color(255, 255, 255,
				m_background.getFillColor().a - 1));
			m_background.setRadius(m_background.getRadius() - 0.5f);
			m_background.setOrigin(m_background.getRadius(),
				m_background.getRadius());
	}

	timer += deltaTime.asSeconds();
}


//------------------------ setLoadingBarAnimation ------------------------
// Sets the loading bar animation.
// According to the time passed, sets the next animation that will be 
// displayed.
//------------------------------------------------------------------------
void LoadingScreen::setLoadingBarAnimation(int& index)
{
	if (loadingBarAnim.getElapsedTime().asSeconds() > 0.3f)
	{
		loadingRect.left += 182;
		if (loadingRect.left > 546.f)
		{
			if (index <= CIRCLES_LOAD_NUM) 
			{
				index++;
				loadingRect.left = 0;
			}
		}
		else
		{
			m_loadingBar[index].setTextureRect(loadingRect);
			loadingBarAnim.restart();
		}
	}
}


//---------------------------- setLoadingBar -----------------------------
// Sets the loading bars stats.
// i.e. sets its position, size, origin and so on.
//------------------------------------------------------------------------
void LoadingScreen::setLoadingBar()
{
	m_loadingBar.resize(5);
	loadingRect = LOADING_INTRECT;

	for (int i = 0; i < m_loadingBar.size(); i++) 
	{
		m_loadingBar[i].setSize({ LOADING_BAR_WIDTH,LOADING_BAR_HEIGHT });

		m_loadingBar[i].setTexture(Resources::instance().
			getWindowObjectTexture(Resources::LOADINGBAR));

		m_loadingBar[i].setTextureRect(loadingRect);

		m_loadingBar[i].setPosition(sf::Vector2f((WINDOW_WIDTH * 0.4f) +
			i*(WINDOW_WIDTH / 20.f), 0.7*WINDOW_HEIGHT));

		m_loadingBar[i].setOrigin(loadingBar.getSize() / 2.f);
	}
}


void LoadingScreen::handleHover(const sf::Vector2f&, sf::RenderWindow&) {}

void LoadingScreen::handleClick(const sf::Vector2f&, bool&, int&) {}
