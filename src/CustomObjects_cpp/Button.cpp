//-------------------------- Include section  ----------------------------
#include "Screens_Headers/Button.h"
#include "..\include\Screens_Headers\Button.h"
#include "Macros.h"


//------------------------------- C-tor ----------------------------------
// The C-tor sets all the desired features of the button.
// i.e. sets the position of the button, origin, text, color and style. 
//------------------------------------------------------------------------
Button::Button(const sf::Vector2f& size,
	const sf::Vector2f& pos, const std::string& text)
	: m_background(size), m_text(text,
		*Resources::instance().getArialfont(), 40)
{
	m_background.setPosition(pos);

	m_background.setOrigin(m_background.getSize()/2.f);

	m_text.setOrigin(m_text.getLocalBounds().width/2,
		m_text.getLocalBounds().height / 2);

	m_text.setPosition(pos.x,pos.y-10);

	m_background.setTexture(nullptr);

	m_text.setFillColor(GREY_COLOR);

	m_text.setStyle(sf::Text::Bold);
}


//----------------------------- setPostion -------------------------------
// Sets the button position
//------------------------------------------------------------------------
void Button::setPostion(const sf::Vector2f& position)
{
	m_background.setPosition(position);

	m_text.setPosition(position.x, position.y-5);
}


//----------------------------- handleHover ------------------------------
// Handle mouse hover above button and change
// the texture accordingly.
//------------------------------------------------------------------------
void Button::handleHover(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	if (m_background.getGlobalBounds().contains(location)) 
	{
		if (m_background.getTexture() != Resources::instance().
			getWindowObjectTexture(Resources::BUTTON_HOVER_BACKGROUND)) {

			Resources::instance().playSound(BUTTON_HOVER_SOUND);
			m_background.setTexture(Resources::instance().
				getWindowObjectTexture(Resources::BUTTON_HOVER_BACKGROUND));
			m_text.setFillColor(sf::Color::White);
		}
	}

	else 
	{
		m_background.setTexture(Resources::instance().
			getWindowObjectTexture(Resources::BUTTON_BACKGROUND));
		m_text.setFillColor(GREY_COLOR);
	}
}


//------------------------------ isClicked -------------------------------
// Check if the button was clicked
//------------------------------------------------------------------------
bool Button::isClicked(const sf::Vector2f& location)
{
	if (m_background.getGlobalBounds().contains(location))
	{
		Resources::instance().playSound(BUTTON_CLICKED_SOUND);
		return true;
	}

	return false;
}


//----------------------------- setTexture -------------------------------
// Set texture of the background of the buttons. 
//------------------------------------------------------------------------
void Button::setTexture(sf::Texture* texture)
{
	m_background.setTexture(texture);
}


//----------------------------- setTextColor -----------------------------
// Set the text color apear on the  background.
//------------------------------------------------------------------------
void Button::setTextColor(sf::Color color)
{
	m_text.setFillColor(color);
}


//----------------------------- setTextSize ------------------------------
// Sets the buttuns text size.
//------------------------------------------------------------------------
void Button::setTextSize(const int size)
{
	m_text.setCharacterSize(size);

	m_text.setOrigin(m_text.getLocalBounds().width / 2,
		m_text.getLocalBounds().height / 2);
}


//-------------------------------- draw ----------------------------------
// draw the background and the text of the buttons.
//------------------------------------------------------------------------
void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_text);
}
