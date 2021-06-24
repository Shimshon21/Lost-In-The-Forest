#pragma once

//-------------------------- Include section  ----------------------------
#include "GameObject.h"


//------------------------- class StaticObject  ---------------------------
class StaticObject : public GameObject
{
public:

	// c-tor
	StaticObject(sf::Vector2f, sf::Vector2f);

	// d-tor
	virtual ~StaticObject() = default;

	virtual void draw(sf::RenderWindow&) override;

	virtual void update(const sf::Time&);

private:
};