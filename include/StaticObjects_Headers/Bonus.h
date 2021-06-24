#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObject.h"


//--------------------------- class Bonus --------------------------------
class Bonus : public StaticObject
{
public:

	// c-tor
	Bonus() = default;

	// c-tor
	Bonus(const sf::Vector2f&, const sf::Vector2f&);
	
	// d-tor
	virtual ~Bonus() = default;
};