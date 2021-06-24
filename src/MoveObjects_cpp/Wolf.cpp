//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/Wolf.h"
#include "Resources.h"


//------------------------------- C-tor ----------------------------------
// Uses the base class constructor to initialize the fields.
// Also, sets the wolfs damage and its hp.
//------------------------------------------------------------------------
Wolf::Wolf(const sf::Vector2f& size, const sf::Vector2f& pos)
	: SmartEnemy(size, pos, Resources::instance().
		moveableAnimationsData(Resources::instance().WOLF_DATA))
{
	m_damagePoints = WOLF_HIT_DMG;
	m_health.setHp(WOLF_HP);
}


//------------------------------- update ---------------------------------
// Updates the animation.
//------------------------------------------------------------------------
void Wolf::update(sf::Time delta)
{
	m_animation.update(delta);
}


//-------------------------------- draw ----------------------------------
// Draws the wolf and its stats upon the window of the game.
//------------------------------------------------------------------------
void Wolf::draw(sf::RenderWindow& window)
{
	m_health.setPosition(sf::Vector2f
	(m_shape.getPosition().x - m_shape.getOrigin().x,
		m_shape.getPosition().y - m_shape.getOrigin().y * 1.5f));
	window.draw(m_shape);
	m_health.draw(window);
}


//-------------------------------- move ----------------------------------
// Moves the object. 
// Moves only if he is alive and not getting hit by the player.
//------------------------------------------------------------------------
void Wolf::move()
{
	if (m_health.getHp() > 0 &&
		m_animation.getOperation() != Operation::Hurt)
	{
		SmartEnemy::move();
	}
	else 
	{
		m_animation.operation(Operation::Dead);
	}
}


//---------------------------- playHurtSound -----------------------------
// Plays the hurt sound.
//------------------------------------------------------------------------
void Wolf::playHurtSound() const
{
	Resources::instance().playSound(WOLF_HURT);
}


//--------------------------- playDeathSound -----------------------------
// Plays the death sound.
//------------------------------------------------------------------------
void Wolf::playDeathSound() const
{
	Resources::instance().playSound(WOLF_DEATH);
}


//--------------------------- playAttackSound ----------------------------
// Plays the attack sound.
//------------------------------------------------------------------------
void Wolf::playAttackSound() const
{
	Resources::instance().playSound(WOLF_ATTACK);
}
