#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObject.h"
#include "Animation.h"

//----------------------------- class Key  -------------------------------
class Key : public StaticObject
{
public:

	// C-tor
	Key(sf::Vector2f);

	// D-tor
	virtual ~Key() = default;

	virtual void update(const sf::Time&)override;

private:

	Animation m_animation;
};