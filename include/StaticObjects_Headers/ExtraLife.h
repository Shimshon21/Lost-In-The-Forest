#pragma once

//-------------------------- Include section  ----------------------------
#include "Bonus.h"
#include "Animation.h"

//-------------------------- class ExtraLife  ----------------------------
class ExtraLife : public Bonus
{
public:

	// c-tor
	ExtraLife() = default;

	// c-tor
	ExtraLife(const sf::Vector2f&);

	// d-tor
	virtual ~ExtraLife() = default;

	virtual void update(const sf::Time&)override;

	virtual void draw(sf::RenderWindow& window)override;

private:
	Animation m_animation;
};