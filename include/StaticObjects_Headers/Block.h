#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObject.h"
#include "StaticObjects_Headers/Block.h"
#include "Macros.h"


//--------------------------- Include Block  -----------------------------
class Block: public StaticObject
{
public:

	// c-tor
	Block(sf::Vector2f, char, const int);

	// d-tor
	virtual ~Block() = default;

private:

	sf::IntRect m_rect;

	void setFirstStage(char, const sf::Vector2f&);
	
	void setSecondStage(char, const sf::Vector2f&);
	
	void setThirdStage(char, const sf::Vector2f&);
};

