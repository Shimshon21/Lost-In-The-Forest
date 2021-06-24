#pragma once

//-------------------------- Include section  ----------------------------
#include "ScreenBase.h"
#include "SFML/Graphics.hpp"
#include "Button.h"


//----------------------- class EndGameScreen  ----------------------------
class EndGameScreen: public ScreenBase
{
public:

	// C-tor
	EndGameScreen();

	// D-tor
	virtual ~EndGameScreen() = default;

	virtual void intialScreenSet() override;

	virtual void draw(sf::RenderWindow&) override;

	void setEndGameData(const std::string&, const std::string&);

protected:

	virtual void handleHover(const sf::Vector2f&,
		sf::RenderWindow&) override;

	virtual void handleClick(const sf::Vector2f&, bool&, int&) override;

private:

	void setTextData();

	void setTextData(sf::Text& text, const int,
		const sf::Vector2f&, const std::string&, const int);

	// Amount of gems were existed in the whole game.
	int gemsCollecttedOverall = 0;;

	sf::RectangleShape m_background;

	Button backToMenuBtn;

	sf::Text endingTitle, scoreText,
		lifesLostText, stageEnded;
};