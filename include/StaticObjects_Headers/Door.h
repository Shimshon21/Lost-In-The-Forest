#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObject.h"


//---------------------------- class Door --------------------------------
class Door : public StaticObject
{
public:

	// c-tor
	Door(sf::Vector2f);
	
	// d-tor
	virtual ~Door() = default;

private:
};