//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/Crow.h"
#include "Resources.h"


//-------------------------------- Crow ----------------------------------
// Uses the base class constructor to initialize the fields.
// Also, sets the crows damage and its hp.
//------------------------------------------------------------------------
Crow::Crow(sf::Vector2f size, sf::Vector2f pos) :
	SmartEnemy(size, pos,Resources::instance().
		moveableAnimationsData(Resources::CROW_DATA))
{
	m_damagePoints = CROW_HIT_DMG;

	m_health.setHp(CROW_HP);

}


//------------------------------- update ---------------------------------
// Updates the animation.
//------------------------------------------------------------------------
void Crow::update(sf::Time delta)
{
	m_animation.update(delta);
}


//-------------------------------- draw ----------------------------------
// Draws the object upon the window of the world.
//------------------------------------------------------------------------
void Crow::draw(sf::RenderWindow& window)
{
	m_health.setPosition(sf::Vector2f
	(m_shape.getPosition().x - m_shape.getOrigin().x,
		m_shape.getPosition().y - m_shape.getOrigin().y * 1.5f));

	window.draw(m_shape);

	m_health.draw(window);
}


//-------------------------------- move ----------------------------------
// Moves the crow.
// This is a smart obejct. Therefore, it move smart if the player is 
// close. Otherwise, it moves normally.
//------------------------------------------------------------------------
void Crow::move()
{
	if (m_health.isAlive() &&
		m_animation.getOperation() != Operation::Hurt)
	{
		SmartEnemy::move();
	}
	else 
	{
		Enemy::move(DOWN_MOVEMENT);
	}
}


//---------------------------- handleCollision ---------------------------
// Handles collision with the floor.
// This is a flying object. Therefore, it has a unique handle floor/block
// than the other moveobject that more on land.
//------------------------------------------------------------------------
void Crow::handleCollision(Block& floor)
{
	if (!m_health.isAlive()) 
	{
		m_animation.operation(Operation::Dead);
		m_shape.setPosition(m_shape.getPosition().x,
			m_shape.getPosition().y + m_shape.getOrigin().y / 2);
	}

	Enemy::handleCollision(floor);
}


//----------------------------- handleFall -------------------------------
// Handle fall.
// This is a flying object. Therefore it handles fall if it is dead.
//------------------------------------------------------------------------
void Crow::handleFall() 
{
	if (m_health.getHp() <= ZERO) 
	{
		Enemy::handleFall();
	}
}


//---------------------------- playDeathSound ----------------------------
// Plays the hurt sound.
//------------------------------------------------------------------------
void Crow::playHurtSound() const
{
	Resources::instance().playSound(CROW_HURT);
}


//---------------------------- playDeathSound ----------------------------
// Plays the death sound.
//------------------------------------------------------------------------
void Crow::playDeathSound() const
{
	Resources::instance().playSound(CROW_DEATH);
}


//---------------------------- playAttackSound ---------------------------
// Plays the attack sound.
//------------------------------------------------------------------------
void Crow::playAttackSound() const
{
	Resources::instance().playSound(CROW_ATTACK);
}