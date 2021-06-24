#pragma once
#include "SFML/Graphics.hpp"
#include "StaticObject.h"

class Decoration:public StaticObject
{
public:

	// c-tor
	Decoration(const sf::Vector2f&, const char, const int);
		
	// d-tor
	virtual ~Decoration() = default;

private:

	void setStageOneDecoration(const char);

	void setStageTwoDecoration(const char);

	void setStageThreeDecoration(const char);

	sf::IntRect m_rect;
};