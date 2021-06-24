#pragma once

//-------------------------- Include section  ----------------------------
#include "ScreenBase.h"
#include "Button.h"


//--------------------- Class InstructionScreen  -------------------------
class InstructionScreen: public ScreenBase
{
public:
	
	// C-tor
	InstructionScreen();

	// D-tor
	virtual ~InstructionScreen() = default;

	virtual void intialScreenSet() override;

	virtual void draw(sf::RenderWindow& window) override;

protected:

	virtual void handleHover(const  sf::Vector2f&,
		sf::RenderWindow&) override;

	virtual void handleClick(const  sf::Vector2f&,
		bool&, int&) override;


private:

	void setTextData(sf::Text&, const int,
		const sf::Vector2f&, const std::string&, const int);

	void setButtons();

	void setText();

	void showDescriptionsScreen(sf::RenderWindow&);

	void showControlsScreen(sf::RenderWindow&);

	bool showControls = false;

	sf::Text gamePlayDescTitle,
		gamplayDescription,
		buttonKeysTitle,
		keysOperationsTitle,
		KeysDiscription;

	Button backButton,
		showControlsButton,
		showDescriptionButton,
		arrowsLeftRightButton,
		spaceKeyButton,
		xKeyButton,
		zKeyButton,
		rKeyButton;

	sf::RectangleShape m_background;
};