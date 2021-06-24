//-------------------------- Include section  ----------------------------
#include "MoveObjects_Headers/Enemy.h"
#include "CollisionHandling.h"
#include "Resources.h"


//-------------------------------- C-tor ---------------------------------
// Sets enemy features using the base class constructor.
//------------------------------------------------------------------------
Enemy::Enemy(const sf::Vector2f& size, const sf::Vector2f& pos,
	const AnimationData& data)
	: MoveObject(size, pos), m_health
	(sf::Vector2f(m_shape.getSize().x, 4), { 0.f,0.f }),
	m_animation(data, Operation::Right, m_shape,
		Resources::instance().getMovableObjectTexture
		(Resources::instance().ENEMIES))
{
	setEventsClock();
}


//-------------------------------- move ----------------------------------
// Moves the enemy.
// The function works as follows:
// 1. checks if the movement is legal.
// 2. if the movement was legal, 
//------------------------------------------------------------------------
void Enemy::move(const sf::Vector2f& movement)
{
	onFloor = false;
	
	m_oldPos = m_shape.getPosition();
	m_shape.move(movement);
	
	MoveObject::handleEvents();
}


//---------------------------- handleCollision ---------------------------
// Handles collision with the floor.
// Pushes the enemy to the previous position, before the collision
// depending on where the collision with the floor was.
// For example, if the collision was from below, it pushes the moveobject 
// downwards, if it was from left, it pushes to right and so on.
//------------------------------------------------------------------------
void Enemy::handleCollision(Block& floor)
{
	if (m_shape.getPosition().y <= 
		(floor.getPosition().y - floor.getShape().y / 2))
	{
		m_shape.setPosition(m_oldPos);
		falling = false;
		onFloor = true;
	}
	else if (collisionFromLeft(floor))
	{
		m_shape.move(-PUSH_FROM);
	}
	else if (collisionFromRight(floor))
	{
		m_shape.move(PUSH_FROM);
	}
	else if (collisionFromBelow(floor))
	{
		m_shape.setPosition(m_oldPos);
	}
}


//--------------------------- handleCollision ----------------------------
// Handle collision with the box.
// Pushes the enemy to the previous position, before the 
// collision depending on where the collision with the box was.
//------------------------------------------------------------------------
void Enemy::handleCollision(Box& box)
{
	if (CollisionFromAboveBox(box))
	{
		m_shape.setPosition(m_oldPos);
		falling = false;
		onFloor = true;
	}
	else if (collisionFromLeft(box))
	{
		m_shape.move(RIGHT_MOVEMENT);
	}
	else if (collisionFromRight(box))
	{
		m_shape.move(LEFT_MOVEMENT);
	}
	else if (collisionFromBelow(box))
	{
		m_shape.move(UP_MOVEMENT);
	}
}


//------------------------------ handleFall ------------------------------
// The enemy handles fall.
// Handles fall only if not on the floor.
//------------------------------------------------------------------------
void Enemy::handleFall()
{
	if (!onFloor)
	{
		inHandleFall = true;
		falling = true;

		move(DOWN_MOVEMENT);
		
		inHandleFall = false;
	}
}


//---------------------------- isPlayerClose -----------------------------
// Returns if the player is close.
//------------------------------------------------------------------------
bool Enemy::isPlayerClose()
{
	return (std::abs(m_shape.getPosition().x -
		getPlayerPos().x) < m_shape.getSize().x * 5);
}


//------------------------------- isAlive --------------------------------
// Returns if the enemy is alive.
//------------------------------------------------------------------------
bool Enemy::isAlive()
{
	return m_health.isAlive();
}


//--------------------------------- hit ----------------------------------
// Performs a hit operation.
// We will reach this function only if the player the enemy have collided.
// The function recives the enemy with which the collision was and
// activates polymorphic functions that are unique to the specific type
// of enemy.
//------------------------------------------------------------------------
void Enemy::hit(Enemy& e)
{
	if (m_health.isAlive()) 
	{
		if (isEventDelayPassed(FIST_ATTACK) &&
			m_animation.getOperation() != Operation::Hurt)
		{
			m_hitingStatus = true;
			e.playAttackSound();
			scaleAccordingToPlayerPos();
			m_animation.operation(Operation::Hit);
		}
		else 
		{
			m_hitingStatus = false;
		}
	}
}

const int Enemy::getDamagePoints() const
{
	return m_damagePoints;
}


//------------------------------ handleHit -------------------------------
// Handles the player hit.
// Absorbs the blow of the player.
// Uses polymorphic functions activates the appropriate animations and
// sounds.
//------------------------------------------------------------------------
void Enemy::handleHit(Enemy& e, const int damage)
{
	if (m_health.isAlive())
	{
		m_health.decreaseHealth(damage);
		if (m_health.isAlive())
		{
			m_animation.operation(Operation::Hurt);
			e.playHurtSound();
		}
		else
		{
			e.playDeathSound();
		}
	}
	else
	{
		m_animation.operation(Operation::Dead);
	}
}



//------------------------------- getMove --------------------------------
// Return the next move of the Bear.
// The next move is selected by the time passed. 
// The Constant Enemy changes it's scale every X seconds.
//------------------------------------------------------------------------
sf::Vector2f Enemy::getMove()
{
	// static timer to have the movement every X time
	static sf::Clock movementClock;

	if (m_animation.getOperation() == Operation::Hurt ||
		m_animation.getOperation() == Operation::Hit)
	{
		return STAY_IN_PLACE;
	}

	if (movementClock.getElapsedTime().asSeconds() <= TWO_SEC)
	{
		m_animation.operation(Operation::Right);
		m_shape.setScale(SCALE_LEFT);
		return LEFT_MOVEMENT;
	}
	else if (movementClock.getElapsedTime().asSeconds() <= FOUR_SEC)
	{
		m_animation.operation(Operation::Stay);
		return STAY_IN_PLACE;
	}
	else if (movementClock.getElapsedTime().asSeconds() <= SIX_SEC)
	{
		m_animation.operation(Operation::Right);
		m_shape.setScale(SCALE_RIGHT);
		return RIGHT_MOVEMENT;
	}
	else if (movementClock.getElapsedTime().asSeconds() >= SIX_SEC &&
		movementClock.getElapsedTime().asSeconds() <= EIGHT_SEC)
	{
		m_animation.operation(Operation::Stay);
		return STAY_IN_PLACE;
	}
	else 
	{
		movementClock.restart();
		m_shape.setScale(SCALE_LEFT);
		return LEFT_MOVEMENT;
	}

	// default
	return  LEFT_MOVEMENT;
}



//---------------------------- setEventsClock ----------------------------
// Sets the events clock of the current enemy.
//------------------------------------------------------------------------
void Enemy::setEventsClock()
{
	MoveObject::setEventsClock(ENEMY_HIT_RATIO);
}


//---------------------------- setOperation ------------------------------
// sets the operation of the animation.
//------------------------------------------------------------------------
void Enemy::setOperation(const Operation op)
{
	m_animation.operation(op);
}


//----------------------- scaleAccordingToPlayerPos ----------------------
// Scales the enemy according to the player position.
//------------------------------------------------------------------------
void Enemy::scaleAccordingToPlayerPos()
{
	if (m_shape.getPosition().x < getPlayerPos().x)
	{
		m_shape.setScale(SCALE_RIGHT);
	}
	else
	{
		m_shape.setScale(SCALE_LEFT);
	}
}


void Enemy::playDeathSound() const {}

void Enemy::playHurtSound() const {}

void Enemy::playAttackSound() const {}