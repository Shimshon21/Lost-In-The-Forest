//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/StaticObject.h"
#include "Operation.h"


// C-tor
StaticObject::StaticObject(sf::Vector2f size, sf::Vector2f pos)
	: GameObject(size, pos)
{}


//------------------------------ draw ------------------------------------
// Draws the static object upon the window of the game.
//------------------------------------------------------------------------
void StaticObject::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}

void StaticObject::update(const sf::Time&) {}


