#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "ScreenBase.h"
#include "Button.h"


//-------------------------- Class OptionsScreen  ------------------------
class OptionsScreen: public ScreenBase
{
public:

	// C-tor
	OptionsScreen();

	// D-tor
	virtual ~OptionsScreen() = default;

	virtual void draw(sf::RenderWindow&) override;

	virtual void intialScreenSet() override;

	virtual void handleHover(const sf::Vector2f&, sf::RenderWindow&);

	virtual void handleClick(const sf::Vector2f&, bool&, int&);

private:

	Button backToMenuButton;

	void setTextData(sf::Text&, const int, const sf::Vector2f&,
		const std::string&, const int);

	void setTextData();

	void setTextures();

	void setOnTextClick(const sf::Vector2f&);

	void setOnTextHover(const sf::Vector2f&);

	sf::RectangleShape m_background;

	sf::Text m_title, soundEffectTitle,
		musicTitle, allowSound, allowMusic;
};