#pragma once

//-------------------------- Include section  ----------------------------
#include "SpecialAbility.h"
#include "Animation.h"


//-------------------------- class FireArrows  ---------------------------
class FireArrows : public SpecialAbility
{
public:

	// c-tor
	FireArrows(const sf::Vector2f& pos);

	// d-tor
	virtual ~FireArrows() = default;

private:
};