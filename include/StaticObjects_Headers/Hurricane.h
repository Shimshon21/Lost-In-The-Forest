#pragma once

//-------------------------- Include section  ----------------------------
#include "StaticObjects_Headers/StaticObject.h"
#include "Animation.h"

//-------------------------- class Hurricane -----------------------------
class Hurricane : public StaticObject
{
public:

	// c-tor
	Hurricane(sf::Vector2f);

	// d-tor
	virtual ~Hurricane() = default;

	void update(const sf::Time&) override;

private:
	Animation m_animation;
};