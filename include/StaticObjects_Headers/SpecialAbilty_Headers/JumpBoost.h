#pragma once

//-------------------------- Include section  ----------------------------
#include "SpecialAbility.h"
#include "Animation.h"


//-------------------------- class JumpBoost   ----------------------------
class JumpBoost : public SpecialAbility
{
public:
	
	// c-tor
	JumpBoost(const sf::Vector2f& pos);
	
	// d-tor
	virtual ~JumpBoost() = default;

private:
};
