//-------------------------- Include section  ----------------------------
#include "OptionsScreen.h"
#include "Macros.h"
#include "Resources.h"


//---------------------------- Constractor -------------------------------
// Initializing the bacground, text and the buttons of the options screen. 
//------------------------------------------------------------------------
OptionsScreen::OptionsScreen() 
	: m_background({ WINDOW_WIDTH,WINDOW_HEIGHT }), 
backToMenuButton({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
	{ 0.5 * WINDOW_WIDTH,0.8 * WINDOW_HEIGHT }, "Menu")
{
	setTextures();
	setTextData();
}


//------------------------------- draw -----------------------------------
// Draws the Options screen.
// Draws the background, title and buttons. 
//------------------------------------------------------------------------
void OptionsScreen::draw(sf::RenderWindow& window)
{
	window.draw(m_background);	

	window.draw(m_title);			

	window.draw(soundEffectTitle);

	window.draw(musicTitle);

	window.draw(allowSound);

	window.draw(allowMusic);

	backToMenuButton.draw(window);
}


//---------------------------- handleHover -------------------------------
// Handles the event that the mouse hovers the buttons of the menu 
// screen.
//------------------------------------------------------------------------
void OptionsScreen::handleHover(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	backToMenuButton.handleHover(location, window);

	setOnTextHover(location);
}



//----------------------------- handleClick ------------------------------
// Handle the event that the user clicked a button. 
//------------------------------------------------------------------------
void OptionsScreen::handleClick(const sf::Vector2f& location,
	bool& toSwitchScreen, int& switchToScreen)
{
	if (backToMenuButton.isClicked(location))
	{
		toSwitchScreen = true;
		switchToScreen = MENU;
	}

	setOnTextClick(location);
}


//----------------------------- setTextData ------------------------------
// Sets the text data and characteristics.
// i.e. sets the text fond, size, style, color and so on.
//------------------------------------------------------------------------
void OptionsScreen::setTextData(sf::Text& text, const int fontSize,
	const sf::Vector2f& pos, const std::string& str, const int style)
{
	text.setFont(*Resources::instance().getArialfont());
	text.setCharacterSize(fontSize);
	text.setString(str);
	text.setColor(sf::Color::Black);
	text.setStyle(style);

	text.setOrigin(text.getLocalBounds().width / 2,
		text.getLocalBounds().height / 2);
	text.setPosition(pos);
}


//----------------------------- setTextures ------------------------------
// Sets  the textures of the background and the button "back".
//------------------------------------------------------------------------
void OptionsScreen::setTextures()
{
	m_background.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::MENU_BACKGROUND));

	backToMenuButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));
}


//----------------------------- setTextData ------------------------------
// Sets the text features that is displayed on the options screen. 
//------------------------------------------------------------------------
void OptionsScreen::setTextData()
{
	setTextData(m_title, 50,
		{ 0.5 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		"Options ", (sf::Text::Bold | sf::Text::Underlined));

	setTextData(soundEffectTitle, 50,
		{ 0.4 * WINDOW_WIDTH,0.25 * WINDOW_HEIGHT },
		"Sounds Effect: ", (sf::Text::Bold));

	setTextData(musicTitle, 50,
		{ 0.4 * WINDOW_WIDTH,0.4 * WINDOW_HEIGHT },
		"Music: ", (sf::Text::Bold));

	setTextData(allowSound, 50,
		{ 0.6 * WINDOW_WIDTH,0.25 * WINDOW_HEIGHT },
		"Enable", (sf::Text::Bold));

	setTextData(allowMusic, 50,
		{ 0.6 * WINDOW_WIDTH,0.4 * WINDOW_HEIGHT },
		"Enable", (sf::Text::Bold));
}


//--------------------------- setOnTextClick -----------------------------
// Depending on the player's choice, replaces the text displayed on the
// options screen
//------------------------------------------------------------------------
void OptionsScreen::setOnTextClick(const sf::Vector2f& location)
{
	if (allowSound.getGlobalBounds().contains(location))
	{
		if (Resources::instance().isSoundAllowed()) 
		{
			Resources::instance().setSoundStatues(false);
			allowSound.setString(DISABLE);
		}
		else 
		{
			Resources::instance().setSoundStatues(true);
			allowSound.setString(ENABLE);
		}
	}


	if (allowMusic.getGlobalBounds().contains(location))
	{
		if (Resources::instance().isMusicAllowed())
		{
			Resources::instance().setMusicStatues(false);
			Resources::instance().pauseMusic();
			allowMusic.setString(DISABLE);
		}
		else
		{
			Resources::instance().setMusicStatues(true);
			Resources::instance().playMenuSoundTrack();
			allowMusic.setString(ENABLE);
		}
	}
}


//--------------------------- setOnTextHover -----------------------------
// If the mouse is over the text, it increases the size of the text to
// give the player an indication that he can click on that text.
//------------------------------------------------------------------------
void OptionsScreen::setOnTextHover(const sf::Vector2f& location)
{
	if (allowMusic.getGlobalBounds().contains(location))
	{
		allowMusic.setFillColor(sf::Color::White);
	}
	else
	{
		allowMusic.setFillColor(sf::Color::Black);
	}

	if (allowSound.getGlobalBounds().contains(location))
	{
		allowSound.setFillColor(sf::Color::White);
	}
	else
	{
		allowSound.setFillColor(sf::Color::Black);
	}
}


void OptionsScreen::intialScreenSet() {}