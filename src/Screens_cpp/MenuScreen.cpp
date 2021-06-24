//-------------------------- Include section  ----------------------------
#include "Screens_Headers/MenuScreen.h"
#include "Macros.h"
#include "Resources.h"


//------------------------------- C-tor ----------------------------------
// Sets the menu screens features.
// i.e. stes the background picture of the menu screen, title, buttons.
//------------------------------------------------------------------------
MenuScreen::MenuScreen() :
	m_background({ WINDOW_WIDTH,WINDOW_HEIGHT }),
	runGame({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.5 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT }, "Start"),
	showInstruction({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.5 * WINDOW_WIDTH,0.45 * WINDOW_HEIGHT }, "Help"),
	showOptions({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.5 * WINDOW_WIDTH,0.60 * WINDOW_HEIGHT }, "Options"),
	exitGame({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.5 * WINDOW_WIDTH,0.75 * WINDOW_HEIGHT }, "Exit"),
	m_title({ 0.4 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT }),
	m_intro({ WINDOW_WIDTH,WINDOW_HEIGHT })
{
	m_background.setTexture(Resources::instance()
		.getWindowObjectTexture(Resources::MENU_BACKGROUND));

	m_intro.setFillColor(sf::Color::White);

	setTitle();			// Sets the title
	setButtons();		// Sets the buttons

	Resources::instance().playMenuSoundTrack();
}


//------------------------------ draw ------------------------------------
// Draws the menu screen on the window.
//------------------------------------------------------------------------
void MenuScreen::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_title);

	if (m_intro.getFillColor().a == 0.f || 
		m_intro.getPosition().y >= 0.1 * WINDOW_HEIGHT)
	{	
		runGame.draw(window);

		showInstruction.draw(window);

		showOptions.draw(window);

		exitGame.draw(window);
	}
	else
	{
		showIntroAnimation(window);
	}
}


//------------------------- intialScreenSet ------------------------------
// Sets the intial menu screen features.
//------------------------------------------------------------------------
void MenuScreen::intialScreenSet()
{
	Resources::instance().pauseMusic();				// Turns on the music.
	Resources::instance().playMenuSoundTrack();		// Turns on soundTrack.
}


//--------------------------- handleHover --------------------------------
// Handle the event that the mouse hovers the button of the menu screen.
//------------------------------------------------------------------------
void MenuScreen::handleHover(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	if (m_intro.getFillColor().a == 0.f) {

		runGame.handleHover(location, window);

		showInstruction.handleHover(location, window);

		showOptions.handleHover(location, window);

		exitGame.handleHover(location, window);
	}
}


//---------------------------- handleClick -------------------------------
// Handles the envent the mouse button got released on the menu buttons.
//------------------------------------------------------------------------
void MenuScreen::handleClick(const sf::Vector2f& location,
	bool& toSwitchScreen, int& switchToScreen)
{

	if (m_intro.getFillColor().a == 0.f) {

		if (runGame.isClicked(location)) 
		{
			switchToScreen = GAME;
			toSwitchScreen = true;
		}

		if (showInstruction.isClicked(location))
		{
			switchToScreen = HELP;
			toSwitchScreen = true;
		}

		if (showOptions.isClicked(location))
		{
			switchToScreen = OPTIONS;
			toSwitchScreen = true;
		}

		if (exitGame.isClicked(location)) 
		{
			exit(EXIT_SUCCESS);
		}
	}
}


//------------------------------ setTitle --------------------------------
// Sets the features of the title of the menu screen.
// Sets the titles position, texture and size.
//------------------------------------------------------------------------
void MenuScreen::setTitle()
{
	m_title.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::MENU_TITLE));

	m_title.setOrigin(m_title.getSize() / 2.f);

	m_title.setPosition(sf::Vector2f
		{ 0.5 * WINDOW_WIDTH,0.5 * WINDOW_HEIGHT });

	_sleep(5);
}


//----------------------------- setButtons -------------------------------
// Sets the buttons of the menu screen.
// sets their texture. the size of the buttons was Determined in the 
// c-tor.
//------------------------------------------------------------------------
void MenuScreen::setButtons()
{
	Resources& res = Resources::instance();

	runGame.setTexture(res.getWindowObjectTexture
	(Resources::BUTTON_BACKGROUND));

	showInstruction.setTexture(res.getWindowObjectTexture
	(Resources::BUTTON_BACKGROUND));

	showOptions.setTexture(res.getWindowObjectTexture
	(Resources::BUTTON_BACKGROUND));

	exitGame.setTexture(res.getWindowObjectTexture
	(Resources::BUTTON_BACKGROUND));
}


//-------------------------- showIntroAnimation --------------------------
// Displays the into animations when  the player enter the game and 
// the menu screen tuns on.
//------------------------------------------------------------------------
void MenuScreen::showIntroAnimation(sf::RenderWindow& window)
{
	window.draw(m_intro);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_title.setPosition
		(sf::Vector2f{ 0.5 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT });
		m_intro.setFillColor
		(sf::Color(255, 255, 255, 0));
	}
	if (m_introTimer.getElapsedTime().asSeconds() > 0.05) {
		m_introTimer.restart();
		if (m_intro.getFillColor().a > 0.f)
		{
			m_title.move({ 0.f,-1.5 });
			m_intro.setFillColor(sf::Color
			(255, 255, 255, m_intro.getFillColor().a - 1));
		}
	}
}