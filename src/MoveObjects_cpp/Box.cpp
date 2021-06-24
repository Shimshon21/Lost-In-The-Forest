//-------------------------- Include section  ----------------------------
#include "Box.h"


// C-tor
Box::Box(sf::Vector2f size, sf::Vector2f pos)
	: MoveObject(size, pos)
{
	m_texture.loadFromFile(BOX_FILE);
	m_shape.setTexture(&m_texture);
}


//-------------------------------- move ----------------------------------
// Moves the box.
//------------------------------------------------------------------------
void Box::move(const sf::Vector2f& movement)
{
	m_shape.move(movement);
}


//--------------------------- handleCollision ----------------------------
// Handles collision with the floor.
//------------------------------------------------------------------------
void Box::handleCollision(Block& floor)
{
	if (collisionFromLeft(floor))
	{
		m_moveAble = false;
		m_shape.move(-PUSH_FROM);
	}
	else if (collisionFromRight(floor))
	{
		m_moveAble = false;
		m_shape.move(PUSH_FROM);
	}
}


//---------------------------- handleEvents ------------------------------
// handles all the possible events that can happen in the game.
// For example: hitting the wall, falling.
//------------------------------------------------------------------------
void Box::handleEvents()
{
	MoveObject::handleEvents();
}


//----------------------------- isMoveAble -------------------------------
// Return if the box is still moveable.
// The box will not be able to move if one of his sides touched the wall.
//------------------------------------------------------------------------
bool Box::isMoveAble() const
{
	return m_moveAble;
}


