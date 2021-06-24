#pragma once

//--------------------------- Include section  ---------------------------
#include "MoveObject.h"
#include "Animation.h"
#include "AnimationData.h"


//---------------------------- Class Arrow  ------------------------------
class Arrow: public MoveObject
{
public:

	// c-tor
	Arrow(const sf::Vector2f&, const sf::Vector2f&,
		const int, const AnimationData&);

	// d-tor
	virtual ~Arrow() = default;

	virtual void move() override;

	virtual void update(sf::Time);

	void setDamage(const int);

	int getDamage();

private:

	unsigned int m_damage = 0;
	
	sf::Clock m_timer;

	Animation m_animation;
};