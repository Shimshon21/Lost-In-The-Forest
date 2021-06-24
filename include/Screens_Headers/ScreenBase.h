#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"


//Base class of differents screens used in the game
class ScreenBase
{
public:

	// D-tor
	virtual ~ScreenBase() = default;

	// draw all the elemnts used in the screen.
	virtual void draw(sf::RenderWindow& window) = 0;
	
	// First time screen appeared functions.
	virtual void intialScreenSet() = 0;

	// Run the screen buttons and data needed on the run.
	virtual void screenRun(sf::RenderWindow&, bool&, int&);


protected:

	// Handle user hover mouse above buttons.
	virtual void handleHover(const  sf::Vector2f&, sf::RenderWindow&) = 0;

	// Handle user hover mouse above buttons.
	virtual void handleClick(const  sf::Vector2f&, bool&, int&) = 0;

private:


};

//Diffrents screen exists in the game.
enum Screens {
	MENU,
	HELP,
	LOADING,
	WIN,
	GAME,
	OPTIONS,
	MAX_SCREENS,
	EXIT,
	RELOAD
};