//-------------------------- Include section  ----------------------------
#include "Screens_Headers/GameOverPopUp.h"
#include "Macros.h"


//----------------------------- Constractor ------------------------------
// Sets the characteristics of the game over screen.
// i.e. set the origin, texture, size, and so on.
//------------------------------------------------------------------------
GameOverPopUp::GameOverPopUp()
	: m_background({ CAMERA_WIDTH, CAMERA_HEIGHT }),
	restart({ 0.3 * CAMERA_WIDTH,0.1 * CAMERA_HEIGHT },
		{ 0,0 }, "Restart"),
	backToMenu({ 0.3 * CAMERA_WIDTH,0.1 * CAMERA_HEIGHT },
		{ 0,0 }, "Main Menu"),
	exitGame({ 0.3 * CAMERA_WIDTH,0.1 * CAMERA_HEIGHT },
		{ 0,0 }, "Exit Game")
{
	m_background.setOrigin(m_background.getSize() / 2.f);
	m_background.setFillColor(sf::Color(0, 0, 0, 100));

	restart.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));
	backToMenu.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));
	exitGame.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));

	setTextData();
}


//---------------------------- intialScreenSet ---------------------------
// Sets the intial music of the game over screen and the game over 
// soundtrack.
//------------------------------------------------------------------------
void GameOverPopUp::intialScreenSet()
{
	Resources::instance().pauseMusic();
	Resources::instance().playGameOverSoundTrack();
}


//----------------------------- handleHover ------------------------------
// Handles the event that the mouse hovers the game over buttons.
// Behaves according to where the mouse is clicked upon the end game 
// screen.
//------------------------------------------------------------------------
void GameOverPopUp::handleHover(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	restart.handleHover(location, window);
	backToMenu.handleHover(location, window);
	exitGame.handleHover(location, window);
}


//----------------------------- handleClick ------------------------------
// Handles the event that the mouse button got realsed on the end game 
// screen buttons. 
// Acts accordingly to where the click took position. 
//------------------------------------------------------------------------
void GameOverPopUp::handleClick(const sf::Vector2f& location,
	bool& switchScreen, int& requastedScreen)
{
	if (restart.isClicked(location)) 
	{
		switchScreen = true;
		requastedScreen = RELOAD;
	}

	else if (backToMenu.isClicked(location))
	{
		Resources::instance().stopMusic();
		switchScreen = true;
		requastedScreen = MENU;
	}

	else if (exitGame.isClicked(location))
	{
		switchScreen = true;
		requastedScreen = EXIT;
	}
}


//----------------------------- setPostion -------------------------------
// Sets the position of the end game screen.
//------------------------------------------------------------------------
void GameOverPopUp::setPostion(const sf::Vector2f& position)
{
	m_title.setPosition({ position.x,position.y - 0.4f * CAMERA_HEIGHT });

	m_background.setPosition(position);

	restart.setPostion({ position.x,position.y - 0.20f * CAMERA_HEIGHT });

	backToMenu.setPostion(position);

	exitGame.setPostion({ position.x,position.y + 0.20f * CAMERA_HEIGHT });
}


//-------------------------------- draw ----------------------------------
// Draws the end game screen.
//------------------------------------------------------------------------
void GameOverPopUp::draw(sf::RenderWindow& window)
{
	window.draw(m_background);

	restart.draw(window);

	backToMenu.draw(window);

	exitGame.draw(window);

	window.draw(m_title);
}


//----------------------------- setTextData ------------------------------
// Sets the text and characteristics of the game over screen.
//------------------------------------------------------------------------
void GameOverPopUp::setTextData() {

	restart.setTextSize(15);
	backToMenu.setTextSize(15);
	exitGame.setTextSize(15);

	m_title.setFont(*Resources::instance().getArialfont());
	m_title.setCharacterSize(30);
	m_title.setString("You Died");
	m_title.setColor(sf::Color::White);
	m_title.setStyle(sf::Text::Bold | sf::Text::Underlined);

	m_title.setOrigin(m_title.getLocalBounds().width / 2,
		m_title.getLocalBounds().height / 2);
	m_title.setPosition({ 0.4 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT });
}
