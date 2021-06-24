#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObject.h"


//---------------------------- Class Spike  ------------------------------
class Spike:public StaticObject
{
public:

	// c-tor
	Spike(sf::Vector2f);

	// d-tor
	Spike() = default;

	virtual ~Spike() = default;

private:
};