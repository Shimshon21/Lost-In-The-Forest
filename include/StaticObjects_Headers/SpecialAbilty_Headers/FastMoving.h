#pragma once

//-------------------------- Include section  ----------------------------
#include "SpecialAbility.h"
#include "Animation.h"


//-------------------------- class FastMoving   --------------------------
class FastMoving : public SpecialAbility
{
public:
	
	// c-tor
	FastMoving(const sf::Vector2f&);
	
	// d-tor
	virtual ~FastMoving() = default;

private:
};