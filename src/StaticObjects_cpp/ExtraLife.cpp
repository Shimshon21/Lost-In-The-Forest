//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/ExtraLife.h"
#include "Resources.h"
#include "Macros.h"


// C-tor
ExtraLife::ExtraLife(const sf::Vector2f& pos)
	: Bonus(sf::Vector2f(BLOCK_SIZE / 4, BLOCK_SIZE / 4), pos),
	m_animation(Resources::instance().
		animationWorldData(Resources::EXTRA_LIFE_DATA),
		Operation::Stay, m_shape,
		Resources::instance().
		getStaticObjectTexture(Resources::STATIC_ANIMATED))
{}


//----------------------------- update -----------------------------------
// Updates the animation depending on delta time.
//------------------------------------------------------------------------
void ExtraLife::update(const sf::Time& deltaTime)
{
	m_animation.update(deltaTime);
}


//------------------------------ draw ------------------------------------
// Draws the static object upon the window of the game.
//------------------------------------------------------------------------
void ExtraLife::draw(sf::RenderWindow& window)
{
	m_shape.setSize(sf::Vector2f(m_shape.getTextureRect().width / 2,
		m_shape.getTextureRect().height / 2));
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	window.draw(m_shape);
}


