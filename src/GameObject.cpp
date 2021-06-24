//-------------------------- Include section  ----------------------------
#include "GameObject.h"


//------------------------------ C-tor -----------------------------------
// Receives the data regarding the object and sets the basic 
// Characteristics. i.e. sets the scale, position, size, and the origin 
// of the gameobject. 
//------------------------------------------------------------------------
GameObject::GameObject(const sf::Vector2f& size, const sf::Vector2f& pos)
{
	m_shape.setScale(1, 1);
	m_shape.setPosition(pos);
	m_shape.setSize(size);
	m_shape.setOrigin(sf::Vector2f({ size.x / 2,size.y / 2 }));
}


//------------------------------ draw ------------------------------------
// Draw the object upon the window of the game.
//------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}


//------------------------------ collide ---------------------------------
// Return if the other gameObject collides with the this one.
//------------------------------------------------------------------------
bool GameObject::collide(GameObject& b) const
{
	return m_shape.getGlobalBounds().
		intersects(b.m_shape.getGlobalBounds());
}


//----------------------------- getPosition ------------------------------
// Return the position of the object.
//------------------------------------------------------------------------
const sf::Vector2f GameObject::getPosition() const
{
	return m_shape.getPosition();
}


//------------------------------ getShape --------------------------------
// Return the shape of the object.
//------------------------------------------------------------------------
const sf::Vector2f GameObject::getShape() const
{
	return m_shape.getSize();
}


//---------------------------- setDisappear ------------------------------
// Update that the object should disappear.
//------------------------------------------------------------------------
void GameObject::setDisappear(bool status)
{
	m_disappear = status;
}


//-------------------------- getDisapperStatus ---------------------------
// Returns whether the object still exists.
//------------------------------------------------------------------------
const bool GameObject::getDisapperStatus() const
{
	return m_disappear;
}


//------------------------------------------------------------------------
// Set the scale of the object.
//------------------------------------------------------------------------
void GameObject::setScale(const sf::Vector2f& scale)
{
	m_shape.setScale(scale);
}