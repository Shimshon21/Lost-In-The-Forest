
//-------------------------- Include section  ----------------------------
#include "Screens_Headers/InstructionScreen.h"
#include "Macros.h"


//--------------------------- Constructor --------------------------------
// Sets the size and texture of the instruction screen.
// Also, sets the instructions screen's buttons position.
//------------------------------------------------------------------------
InstructionScreen::InstructionScreen()
	: m_background({ WINDOW_WIDTH,WINDOW_HEIGHT }),
	backButton({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.2 * WINDOW_WIDTH,0.8 * WINDOW_HEIGHT }, "Menu"),

	showControlsButton({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.8 * WINDOW_WIDTH,0.8 * WINDOW_HEIGHT }, "Controls"),

	showDescriptionButton({ 0.2 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.2 * WINDOW_WIDTH,0.8 * WINDOW_HEIGHT }, "Description"),

	arrowsLeftRightButton({ 0.15 * WINDOW_WIDTH,0.1 * WINDOW_HEIGHT },
		{ 0.585 * WINDOW_WIDTH,0.175 * WINDOW_HEIGHT }, ""),

	spaceKeyButton({ 0.15 * WINDOW_WIDTH,0.09 * WINDOW_HEIGHT },
		{ 0.585 * WINDOW_WIDTH,0.305 * WINDOW_HEIGHT }, ""),

	xKeyButton({ 0.06 * WINDOW_WIDTH,0.09 * WINDOW_HEIGHT },
		{ 0.54 * WINDOW_WIDTH,0.43 * WINDOW_HEIGHT }, ""),

	zKeyButton({ 0.06 * WINDOW_WIDTH,0.09 * WINDOW_HEIGHT },
		{ 0.54 * WINDOW_WIDTH,0.56 * WINDOW_HEIGHT }, ""),

	rKeyButton({ 0.06 * WINDOW_WIDTH,0.09 * WINDOW_HEIGHT },
		{ 0.54 * WINDOW_WIDTH,0.69 * WINDOW_HEIGHT }, "")
{
	setButtons();
	setText();
}


//--------------------------- intialScreenSet ----------------------------
// Sets the intial screen to not show the controls.
//------------------------------------------------------------------------
void InstructionScreen::intialScreenSet()
{
	showControls = false;
}


//----------------------------- handleHover ------------------------------
// Handles the event that mouse hovers the instruction screen.
//------------------------------------------------------------------------
void InstructionScreen::handleHover(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	if (!showControls)
	{
		backButton.handleHover(location, window);

		showControlsButton.handleHover(location, window);
	}
	else
	{
		showDescriptionButton.handleHover(location, window);
	}
}


//---------------------------- handleClick -------------------------------
// Handles click event uppon the instruction screen.
//------------------------------------------------------------------------
void InstructionScreen::handleClick(const sf::Vector2f& location,
	bool& toSwitchScreen, int& switchToScreen)
{
	if (!showControls)
	{
		if (showControlsButton.isClicked(location))
			showControls = true;

		if (backButton.isClicked(location))
		{
			toSwitchScreen = true;
			switchToScreen = MENU;
		}
	}
	else
	{
		if (showDescriptionButton.isClicked(location))
			showControls = false;
	}
}


//------------------------------- draw -----------------------------------
// Draws the instruction screen.
//------------------------------------------------------------------------
void InstructionScreen::draw(sf::RenderWindow& window)
{
	window.draw(m_background);

	if (!showControls)
	{
		showDescriptionsScreen(window);
	}
	else 
	{
		showControlsScreen(window);
	}
}


//--------------------------- setTextData --------------------------------
// Sets the text of the instruction screen.
//------------------------------------------------------------------------
void InstructionScreen::setTextData(sf::Text& text, const int fontSize,
	const sf::Vector2f& pos, const std::string& str, const int style)
{
	text.setFont(*Resources::instance().getArialfont());
	text.setCharacterSize(fontSize);
	text.setString(str);
	text.setColor(sf::Color::Black);
	text.setStyle(style);

	text.setOrigin(text.getLocalBounds().width /
		2, text.getLocalBounds().height / 2);
	text.setPosition(pos);
}


//---------------------------- setButtons --------------------------------
// Sets the button of the instructions screen.
//------------------------------------------------------------------------
void InstructionScreen::setButtons()
{
	m_background.setTexture(Resources::instance()
		.getWindowObjectTexture(Resources::MENU_BACKGROUND));

	backButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));

	showControlsButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));

	showDescriptionButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::BUTTON_BACKGROUND));

	arrowsLeftRightButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::ARROWS_KEY));

	spaceKeyButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::SPACE_KEY));

	xKeyButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::LETTER_X));

	zKeyButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::LETTER_Z));

	rKeyButton.setTexture(Resources::instance().
		getWindowObjectTexture(Resources::LETTER_R));
}


//------------------------------ setText ---------------------------------
// Sets the text of the intial screen.
//------------------------------------------------------------------------
void InstructionScreen::setText()
{
	setTextData(gamePlayDescTitle, 50,
		{ 0.5 * WINDOW_WIDTH,0.05 * WINDOW_HEIGHT },
		"Description", (sf::Text::Bold | sf::Text::Underlined));

	setTextData(buttonKeysTitle, 60, 
		{ 0.5 * WINDOW_WIDTH,0.05 * WINDOW_HEIGHT },
		"Controls", (sf::Text::Bold | sf::Text::Underlined));

	setTextData(gamplayDescription, 26,
		{ 0.525 * WINDOW_WIDTH,0.3 * WINDOW_HEIGHT },
		GAMEPLAY_DISCIPRION, (sf::Text::Bold));

	setTextData(KeysDiscription, 60,
		{ 0.4 * WINDOW_WIDTH,0.415 * WINDOW_HEIGHT },
		CONTROLS_DISCIPRION, (sf::Text::Bold));
}


//------------------------ showDescriptionsScreen ------------------------
// Show the descriptions of the game.
//------------------------------------------------------------------------
void InstructionScreen::showDescriptionsScreen(sf::RenderWindow& window)
{
	window.draw(gamePlayDescTitle);
	window.draw(gamplayDescription);
	backButton.draw(window);
	showControlsButton.draw(window);
}


//-------------------------- showControlsScreen --------------------------
//	Show the controls instructions.
//------------------------------------------------------------------------
void InstructionScreen::showControlsScreen(sf::RenderWindow& window)
{
	window.draw(buttonKeysTitle);
	window.draw(KeysDiscription);

	showDescriptionButton.draw(window);
	arrowsLeftRightButton.draw(window);
	spaceKeyButton.draw(window);
	xKeyButton.draw(window);
	zKeyButton.draw(window);
	rKeyButton.draw(window);
}
