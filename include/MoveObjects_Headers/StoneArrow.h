#pragma once

//-------------------------- Include section  ----------------------------
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "MoveObject.h"
#include "Arrow.h"

class StoneArrow: public Arrow
{
public:

	// C-tor
	StoneArrow(const sf::Vector2f&,const sf::Vector2f&, const int);
	
	// d-tor
	virtual ~StoneArrow() = default;
};