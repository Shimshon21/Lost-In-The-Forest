#pragma once

//-------------------------- Include section  ----------------------------
#include "Bonus.h"
#include "Animation.h"


//-------------------------- class ExtraLife  ----------------------------
class Gold : public Bonus
{
public:

	// c-tor
	Gold(const sf::Vector2f& pos);

	// d-tor
	virtual ~Gold() = default;

	void update(const sf::Time& delta)override;

private:
	Animation m_animation;
};