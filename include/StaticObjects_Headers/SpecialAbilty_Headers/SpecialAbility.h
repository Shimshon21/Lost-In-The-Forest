#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/Bonus.h"
#include "AnimationData.h"
#include "Animation.h"

//------------------------ class SpecialAbility  --------------------------
class SpecialAbility : public Bonus
{
public:

	// C-tor
	SpecialAbility(const sf::Vector2f&, const sf::Vector2f&,
		const AnimationData&);

	// D-tor
	virtual ~SpecialAbility() = default;

	virtual void update(const sf::Time&)override;

protected:

	Animation m_animation;

private:
};