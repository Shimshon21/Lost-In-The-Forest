//-------------------------- Include section  ----------------------------
#include "Screens_Headers/EndGameScreen.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Macros.h"


//------------------------------ C-tor -----------------------------------
// Sets the characteristics of the end game screen.
//------------------------------------------------------------------------
EndGameScreen::EndGameScreen()
	: m_background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)),
	backToMenuBtn({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.5 * WINDOW_WIDTH,0.8 * WINDOW_HEIGHT }, "Menu")
{
	m_background.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::END_GAME_BACKGROUND));

	backToMenuBtn.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));

	setTextData();
}


//--------------------------- intialScreenSet ----------------------------
// Initializes the initial fields of the end screen.
//------------------------------------------------------------------------
void EndGameScreen::intialScreenSet()
{
	Resources::instance().stopMusic();
	Resources::instance().playEndGameSoundTrack();
}


//---------------------------- handleHover -------------------------------
// Handle the event that the mouse hovers the end game screen.
//------------------------------------------------------------------------
void EndGameScreen::handleHover(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	backToMenuBtn.handleHover(location, window);
}


//---------------------------- handleClick -------------------------------
// Handles click upon the end game screen.
//------------------------------------------------------------------------
void EndGameScreen::handleClick(const sf::Vector2f& location,
	bool& toSwitchScreen, int& switchToScreen)
{
	if (backToMenuBtn.isClicked(location)) 
	{
		toSwitchScreen = true;
		switchToScreen = MENU;
		Resources::instance().stopMusic();
	}
}


//------------------------------- draw -----------------------------------
// Draws the end game sceen upon the window.
//------------------------------------------------------------------------
void EndGameScreen::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(endingTitle);
	window.draw(scoreText);
	window.draw(lifesLostText);
	backToMenuBtn.draw(window);
}


//--------------------------- setEndGameData -----------------------------
// Sets the end game data.
// i.e. sets the string, origin, position and so on.
//------------------------------------------------------------------------
void EndGameScreen::setEndGameData(const std::string& gemsCollected, 
	const std::string& lifesLostCounter)
{
	scoreText.setString("Gems collected: " + gemsCollected);
	scoreText.setOrigin(scoreText.getLocalBounds().width / 2,
		scoreText.getLocalBounds().height / 2);
	scoreText.setPosition({ 0.5 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT });

	lifesLostText.setString("Lost: " + lifesLostCounter);
	lifesLostText.setOrigin(lifesLostText.getLocalBounds().width / 2,
		lifesLostText.getLocalBounds().height / 2);
	lifesLostText.setPosition({ 0.5 * WINDOW_WIDTH,0.4 * WINDOW_HEIGHT });
}


//----------------------------- setTextData ------------------------------
// Sets the text data of the text that will be shown uppon the end game
// window.
//------------------------------------------------------------------------
void EndGameScreen::setTextData()
{
	setTextData(endingTitle, 80, 
		{ 0.5 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		"The End", (sf::Text::Bold | sf::Text::Underlined));

	setTextData(scoreText, 50, 
		{ 0.5 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT },
		"Gems collected:" , (sf::Text::Bold));

	setTextData(lifesLostText, 50, 
		{ 0.5 * WINDOW_WIDTH,0.5 * WINDOW_HEIGHT },
		"Lost times:", (sf::Text::Bold));
}


//----------------------------- setTextData ------------------------------
// Sets the text data.
// Sets the text's fonts, charcter size, string, color, style, origing 
// and position.
//------------------------------------------------------------------------
void EndGameScreen::setTextData(sf::Text& text, const int fontSize, 
	const sf::Vector2f& pos, const std::string& str, const int style)
{
	text.setFont(*Resources::instance().getArialfont());
	text.setCharacterSize(fontSize);
	text.setString(str);
	text.setColor(sf::Color::White);
	text.setStyle(style);

	text.setOrigin(text.getLocalBounds().width / 2,
		text.getLocalBounds().height / 2);
	text.setPosition(pos);
}
