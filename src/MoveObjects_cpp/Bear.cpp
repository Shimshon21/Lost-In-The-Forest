//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/Bear.h"
#include "Resources.h"
#include "Macros.h"


//------------------------------- C-tor ----------------------------------
// Sets the size, position, data, texture and damage.
//------------------------------------------------------------------------
Bear::Bear(sf::Vector2f size, sf::Vector2f pos)
	: Enemy(size, pos, Resources::instance().moveableAnimationsData
	(Resources::instance().BEAR_DATA))
{
	m_texture.setSmooth(false);
	m_damagePoints = BEAR_HIT_DMG;
}


//------------------------------- move -----------------------------------
// Move the object. 
// Allows moving only if not falling and not dead.
//------------------------------------------------------------------------
void Bear::move()
{
	if (m_health.isAlive()) 
	{
		if (!falling)
		{
			Enemy::move(getMove() * m_deltaTime * ENEMY_SPEED);
		}
	}
	else 
	{
		m_animation.operation(Operation::Dead);
	}
}


//-------------------------------- update --------------------------------
// Updates the animation.
//------------------------------------------------------------------------
void Bear::update(sf::Time delta)
{
	m_animation.update(delta);
}


//-------------------------------- draw ----------------------------------
// Draws the Bear with the needed animations.
//------------------------------------------------------------------------
void Bear::draw(sf::RenderWindow& window)
{
	m_health.setPosition(sf::Vector2f(m_shape.getPosition().x
		- m_shape.getOrigin().x * 0.9f, m_shape.getPosition().y
		- m_shape.getOrigin().y * 2));

	m_health.draw(window);

	if (m_animation.getOperation() == Operation::Hit) 
	{
		auto temp = m_shape;
		temp.scale(1, 1.5);
		temp.setPosition(temp.getPosition().x,
			temp.getPosition().y - temp.getOrigin().y / 2);
		window.draw(temp);
	}
	else
	{
		window.draw(m_shape);
	}
}


//----------------------------- playHurtSound ----------------------------
// Plays hurt sound.
//------------------------------------------------------------------------
void Bear::playHurtSound() const
{
	Resources::instance().playSound(BEAR_HURT);
}


//---------------------------- playDeathSound ----------------------------
// Plays death sound.
//------------------------------------------------------------------------
void Bear::playDeathSound() const
{
	Resources::instance().playSound(BEAR_DEATH);
}


//---------------------------- playAttackSound ---------------------------
// Plays the attack sound.
//------------------------------------------------------------------------
void Bear::playAttackSound() const {
	Resources::instance().playSound(BEAR_ATTACK);
}
