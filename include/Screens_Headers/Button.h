#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "Resources.h"


//class exihibit buttons used in the screen.
class Button
{
public:

	// Build the background and the text of the button.
	Button(const sf::Vector2f&, const sf::Vector2f&, const std::string&);

	// d-tor
	virtual ~Button() = default;

	// Sets the position of the button.
	void setPostion(const sf::Vector2f&);

	// Handle the mouse hover.
	void handleHover(const sf::Vector2f&, sf::RenderWindow&);

	// Returns if the button is clicked.
	bool isClicked(const sf::Vector2f&);

	// Set the background texture.
	void setTexture(sf::Texture*);

	// Set the text color.
	void setTextColor(sf::Color);

	// Sets the buttsons text size.
	void setTextSize(const int);

	// Draw background and text.
	void draw(sf::RenderWindow&);

private:

	sf::RectangleShape m_background;

	sf::Text m_text;
};