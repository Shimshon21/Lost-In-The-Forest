#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "Screens_Headers/Button.h"
#include "Screens_Headers/ScreenBase.h"


//-------------------------- Class MenuScreen  ---------------------------
class MenuScreen:public ScreenBase
{
public:

	// c-tor
	MenuScreen();
	
	// d-tor
	virtual ~MenuScreen() = default;

	virtual void draw(sf::RenderWindow&) override;

	virtual void intialScreenSet() override;

protected:

	virtual void handleHover(const  sf::Vector2f&, sf::RenderWindow&);

	virtual void handleClick(const  sf::Vector2f&, bool&, int&);

private:

	void setTitle();

	void setButtons();

	void showIntroAnimation(sf::RenderWindow&);

	sf::RectangleShape m_background, m_title, m_intro;

	Button runGame, showInstruction, exitGame, showOptions;

	sf::Clock m_introTimer;
};