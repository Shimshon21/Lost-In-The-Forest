//--------------------------- Include section  ---------------------------
#include "Arrow.h"
#include "Resources.h"


//------------------------------- C-tor ----------------------------------
// Calls the Base class constractor to initialize the fields.
// Also, set the scale of the arrow and restarts the timer.
//------------------------------------------------------------------------
Arrow::Arrow(const sf::Vector2f& size, const sf::Vector2f& pos,
	const int direction, const AnimationData& data)
	: MoveObject(size, pos), m_animation(data, Operation::Stay,
		m_shape, Resources::instance().
		getMovableObjectTexture(Resources::instance().PLAYER))
{
		m_shape.setScale(m_shape.getScale().x
			* direction, m_shape.getScale().y);
		m_timer.restart();
}


//------------------------------- move -----------------------------------
// Move the arrow and deal with the events that can happen.
// In addition, makes sure that the arrow does not exist for more than
// ARROW_EXIST_TIME.
//------------------------------------------------------------------------
void Arrow::move()
{
	if (m_timer.getElapsedTime().asSeconds() < ARROW_STAY_IN_PLACE_TIME)
	{
		m_shape.move(STAY_IN_PLACE);
	}
	else if (m_timer.getElapsedTime().asSeconds() < ARROW_EXIST_TIME)
	{
		m_shape.move(2 * m_shape.getScale().x, ZERO);
	}
	else
	{
		setDisappear(true);
	}

	handleEvents();
}


//------------------------------ update ----------------------------------
// Update the animation of the arrow by delta time.
//------------------------------------------------------------------------
void Arrow::update(sf::Time delta)
{
	if (m_animation.getCurrentIndex() < ARROW_EXIST_TIME)
	{
		m_animation.update(delta);
	}
}


//------------------------------ setDamage -------------------------------
// Sets the damage of the arrow.
//------------------------------------------------------------------------
void Arrow::setDamage(const int damage)
{
	m_damage = damage;
}


//------------------------------ getDamage -------------------------------
// Return the damage of the Arrow.
//------------------------------------------------------------------------
int Arrow::getDamage()
{
	return m_damage;
}
