#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "ScreenBase.h"


//------------------------ class GameOverPopUp  --------------------------
class GameOverPopUp: public ScreenBase
{
public:
	
	// C-tor
	GameOverPopUp();

	// D-tor
	virtual ~GameOverPopUp() = default;

	virtual void intialScreenSet() override;

	void setPostion(const sf::Vector2f&);

	void draw(sf::RenderWindow&);

protected:

	virtual void handleHover(const  sf::Vector2f&,
		sf::RenderWindow&) override;

	virtual void handleClick(const  sf::Vector2f&, bool&, int&) override;

private:

	void setTextData();

	sf::RectangleShape m_background;
	Button restart, backToMenu, exitGame;
	sf::Text m_title;
};