#pragma once

//--------------------------- Include section  ---------------------------
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "MoveObject.h"
#include "Arrow.h"


//--------------------------- Class fireArrow  ---------------------------
class FireArrow: public Arrow
{
public:

	// c-tor
	FireArrow(const sf::Vector2f&, const sf::Vector2f&, const int);
	
	// d-tor
	virtual ~FireArrow() = default;
};