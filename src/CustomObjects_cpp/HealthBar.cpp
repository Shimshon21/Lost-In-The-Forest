//-------------------------- Include section  ----------------------------
#include "HealthBar.h"


//------------------------------- C-tor ----------------------------------
// The C-tor sets all the desired features of the health bar.
// i.e. sets the position of the health bar, position, color and so on.  
//------------------------------------------------------------------------
HealthBar::HealthBar(sf::Vector2f size, sf::Vector2f pos)
	: m_fullSizeBackground(size)
{
	m_fullSizeBackground.setPosition(sf::Vector2f(pos.x ,pos.y));
	m_fullSizeBackground.setOutlineColor(sf::Color::Black);
	m_fullSizeBackground.setOutlineThickness(1);
	m_fullSizeBackground.setFillColor(sf::Color::Red);

	m_currentHealth.setPosition(sf::Vector2f(pos.x,pos.y));
	m_currentHealth.setSize(sf::Vector2f(size.x, size.y )); 
	m_currentHealth.setFillColor(sf::Color::Green);
}


//------------------------- updateCurrentHealth --------------------------
// Updates the current amount of health.
//------------------------------------------------------------------------
void HealthBar::updateCurrentHealth()
{
	if (m_hp > 100) {
		m_hp = 100;
	}
	else if (m_hp < 0) {
		m_hp = 0;
	}

	m_currentHealth.setSize(sf::Vector2f
	(m_fullSizeBackground.getSize().x * m_hp * 0.01,
		m_fullSizeBackground.getSize().y));
}


//---------------------------- decreaseHealth ----------------------------
// Decrease the hp by given integer.
//------------------------------------------------------------------------
void HealthBar::decreaseHealth(const int healthDec)
{
	m_hp -= healthDec;
	updateCurrentHealth();
}


//---------------------------- increaseHealth ----------------------------
// Increase health by given integer.
//------------------------------------------------------------------------
void HealthBar::increaseHealth(const int healthInc)
{
	m_hp += healthInc;
	updateCurrentHealth();

}


//----------------------------- setPosition ------------------------------
// Sets the Position of the health bar upon the window.
//------------------------------------------------------------------------
void HealthBar::setPosition(sf::Vector2f pos)
{
	m_playerIcon.setPosition(pos);

	m_fullSizeBackground.setPosition(
		sf::Vector2f(pos.x , pos.y));

	m_currentHealth.setPosition(
		sf::Vector2f(pos.x , pos.y));
}


//------------------------------- getHp ----------------------------------
// Returns the moveables object hp.
//------------------------------------------------------------------------
const int HealthBar::getHp() const
{
	return m_hp;
}


//------------------------------ isAlive ---------------------------------
// Returns if the moveable object is still alive.
//------------------------------------------------------------------------
const bool HealthBar::isAlive() const
{
	return m_hp > 0;
}


//-------------------------------- draw ----------------------------------
// Draws the health bar upon the window.
//------------------------------------------------------------------------
void HealthBar::draw(sf::RenderWindow& window)
{
	window.draw(m_playerIcon);
	window.draw(m_fullSizeBackground);
	window.draw(m_currentHealth);
}


//------------------------------------------------------------------------
// Sets the amount of hp.
//------------------------------------------------------------------------
void HealthBar::setHp(const int hp)
{
	m_hp = hp;
}
