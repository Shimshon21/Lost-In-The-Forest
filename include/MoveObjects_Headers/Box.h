#pragma once

//-------------------------- Include section  ----------------------------
#include "MoveObject.h"


//---------------------------- class Box ---------------------------------
class Box : public MoveObject
{
public:

	// d-tor
	Box(sf::Vector2f, sf::Vector2f);

	// d-tor
	virtual ~Box() = default;

	void move(const sf::Vector2f&);

	virtual void handleCollision(Block&);

	void handleEvents();

	bool isMoveAble() const;

private:

	bool m_moveAble = true;
};